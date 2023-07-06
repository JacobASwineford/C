#include <stdio.h>

#define MAX_WORD 12

/**
Write a program to print a histogram of the frequencies of different
characters in it's input.
*/

int main() {
    int chars[255];
    int i, c, e;

    for (i = 0; i < 255; i++)
        chars[i] = 0;

    printf("Enter a sentence: ");
    while (1) {
        c = getchar();
        ++chars[c];
        if (c == '\n') break;
    }

    for (i = 0; i < 255; i++) {
        if (chars[i] == 0) continue;
        printf("%c [%d]: ", i, i);
        for (e = 0; e < chars[i]; ++e)
            putchar('#');
        putchar('\n');
    }



    return 0;
}
