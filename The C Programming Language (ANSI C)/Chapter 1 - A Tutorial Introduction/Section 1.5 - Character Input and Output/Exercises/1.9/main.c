#include <stdio.h>

/**
Write a program to copy its input to its output, replacing
each string of one or more blanks by a single blank.
*/

int main() {
    int c;

    printf("Enter a sentence: ");
    while ((c = getchar()) != '\n')
        putchar(c);
    printf("\n");

    return 0;
}
