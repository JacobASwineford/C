#include <stdio.h>

#define N 4
#define STRLEN 50
#define SPACES 4

/**
Write a program detab that replaces tabs in the input
with the proper number of blanks to space to the next tab
stop. Assume a fixed set of tab stops, say every n columns.
Should n be a variable or a symbolic parameter?

n can be either a variable or a symbolic parameter.
Since n does not change, however, I would say it
is much better suited to be a symbolic constant.

Im unsure why the fixed number columns between tab stops is needed.
*/

void detab(char[], int);
void print(char[]);

int main() {
    char str[STRLEN] = "Hello\tthere, nice to\tmeet you.";
    print(str);
    detab(str, STRLEN);
    print(str);

    return 0;
}

/**
Replaces the tabs in the given string with an equivalent number
of spaces. One tab stop is equal to 4 spaces.

This method changes the original array, and needs memory
for spaces to be appended. It will assume that the given char[]
has allocated space for this.
*/
void detab(char sen[], int len) {
    char cpy[len];
    int cpyin = 0;
    char c;
    int in = 0;
    int spaces = SPACES;
    c = sen[in];
    while (c) {
        if (c == '\t') {
            while (spaces--)
                cpy[cpyin++] = ' ';
            spaces = SPACES;
        } else {
            cpy[cpyin++] = sen[in];
        }
        c = sen[++in];
    }

    int i;
    for (i = 0; i < cpyin; i++)
        sen[i] = cpy[i];
}

/**
prints the given char array, and highlights space characters
and tab characters by replacing them when printing. This does
not replace them in memory.
*/
void print(char str[]) {
    int i = 0;
    char c = str[i];
    while (c) {
        if (c == ' ')
            putchar('!');
        else if (c == '\t')
            putchar('?');
        else
            putchar(c);
        c = str[++i];
    }
    putchar('\n');
}
