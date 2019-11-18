#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;

    printf("Hello world\n");

    for (i = 0; i < argc; i++) {
        printf("argv[%d]: %p %s\n", i, (void *)(argv + i), argv[i]);
    }
    return 0;
}
