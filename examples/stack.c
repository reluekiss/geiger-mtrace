#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct StackNode {
    void *ptr;
    size_t size;
    struct StackNode *next;
} StackNode;

int main(void) {
    srand(time(NULL));
    StackNode *stack = NULL;

    while (1) {
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
        } else { // pop
            if (stack) {
                StackNode *node = stack;
                stack = node->next;
                printf("pop: free(%zu) at %p\n", node->size, node->ptr);
                free(node->ptr);
                free(node);
            } else {
                printf("pop: stack empty\n");
            }
        }
        usleep(100000);
    }

    return 0;
}
