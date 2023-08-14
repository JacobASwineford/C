#include <stdio.h>

int main() {
    int i = 40;
    if (i = 5 == 5)
        printf("Hello world!\n");
    else
        printf("False?\n"); // never going to run, sorry

    printf("%d, %d\n", i, i << 1 >> 0);
    return 0;
}
