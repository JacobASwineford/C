#include <stdio.h>

#define SPACES 4
#define LEN 50

/**
Write a program entab that replaces strings of blanks
by the minimum number of spaces and blanks to achieve the same
spacing. Use the same tab stops as for detab. When either a tab or a
single blank would suffice to reach a tab stop, which should be given
preference?

Given the nature of this program, and for general printing purposes,
a blank would be more appropriate to reach a tab stop than a tab.
*/

void detab(char[], int);
void entab(char[], int);
int sequence(char[], int, char);
void print(char[]);

int main() {
    char sen[LEN] = "hello,         how do.         ";
    print(sen);
    entab(sen, LEN);
    print(sen);

    return 0;
}

/**
Entabs the given char array by inserting tabs at appropriate locations.
These tabs are inserted in the place of a specified number of spaces,
defined by the preprocessor variable SPACES.
*/
void entab(char sen[], int len) {
    char cpy[len];
    int cpyin = 0;
    char c;
    int in = 0;
    int i;
    int numspaces;
    c = sen[in];
    while (in < len) {
        if (c == ' ' && sequence(sen, in, ' ') >= SPACES) {
            cpy[cpyin++] = '\t';
            in += SPACES;
        } else {
            cpy[cpyin++] = sen[in++];
        }
        c = sen[in];
    }
    sen[in + 1] = '\0';

    for (i = 0; i < cpyin; i++)
        sen[i] = cpy[i];
}

/**
Checks how many characters are in a row, starting at the specified
position. This includes the character at the specified position.
*/
int sequence(char sen[], int in, char check) {
    char c = sen[in];
    int ret = 0;
    while (c == check) {
        ret++;
        c = sen[++in];
    }
    return ret;
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
