#include <stdio.h>

/**
Write a program to count blanks, tabs, and newlines.
*/

int main() {
    int c, n1;

    n1 = 0;
    while ((c != getchar()) != EOF)
        if (c == '\n' || c == ' ' || c == '\t')
            ++n1;
    printf("%d\n", n1);
}
