#include <stdio.h>

/**
Write a program that prints its input one word per line.
*/

int main() {
    int c;

    printf("Enter a sentence: ");
    while ((c = getchar()) != '\n') {
        if (c == ' ')
            putchar('\n');
        else
            putchar(c);
    }
    return 0;
}
