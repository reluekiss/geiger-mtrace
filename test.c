#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void) {
    srand(time(NULL));

    while (1) {
        if (rand() % 2 == 0) {
            size_t size = (rand() % 1024) + 1;
            void *ptr = malloc(size);
            printf("malloc(%zu) at %p\n", size, ptr);
            free(ptr);
        }
        usleep(50000); 
    }

    return 0;
}
