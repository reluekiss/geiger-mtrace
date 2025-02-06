#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <time.h>
#include <unistd.h>

typedef struct StackNode {
    void *ptr;
    size_t size;
    struct StackNode *next;
} StackNode;

#define MAX_POINTS 800

int main(void)
{
    srand(time(NULL));
    StackNode *stack = NULL;

    int stackCounter = 0;

    int screenWidth = 800;
    int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Malloc based stock counter");

    Vector2 points[MAX_POINTS];
    int pointCount = 0;
    int scale = 5;

    while (!WindowShouldClose())
    {
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        if (rand() % 2 == 0) { // push
            size_t size = (rand() % 1024) + 1;
            void *ptr = malloc(size);
            if (!ptr) exit(EXIT_FAILURE);
            StackNode *node = malloc(sizeof(StackNode));
            if (!node) exit(EXIT_FAILURE);
            node->ptr = ptr;
            node->size = size;
            node->next = stack;
            stack = node;
            printf("push: malloc(%zu) at %p\n", size, ptr);
            stackCounter += 1;
        } else { // pop
            if (stack) {
                StackNode *node = stack;
                stack = node->next;
                printf("pop: free(%zu) at %p\n", node->size, node->ptr);
                free(node->ptr);
                free(node);
                stackCounter -= 1;
            } else {
                printf("pop: stack empty\n");
            }
        }

        if (pointCount < MAX_POINTS) {
            points[pointCount].x = pointCount;
            points[pointCount].y = screenHeight/2 - stackCounter * scale;
            pointCount++;
        } else {
            for (int i = 1; i < MAX_POINTS; i++) {
                points[i-1] = points[i];
                points[i-1].x = i-1;
            }
            points[MAX_POINTS-1].x = MAX_POINTS-1;
            points[MAX_POINTS-1].y = screenHeight/2 - stackCounter * scale;
        }

        BeginDrawing();
            ClearBackground(GRAY);
            if (pointCount > 1)
                DrawLineStrip(points, pointCount, RED);
            DrawLine(0, screenHeight/2, screenWidth, screenHeight/2, BLACK);
        EndDrawing();

        usleep(100000);
    }

    CloseWindow();
    return 0;
}
