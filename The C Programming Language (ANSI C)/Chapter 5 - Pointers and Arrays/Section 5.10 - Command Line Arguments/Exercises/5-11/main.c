#include "../../../../Tools/tokens.c";
#include <stdio.h>

#define SPACES 4
#define LEN 50

/**
Modify the programs entab and detab (written as exercises in
Chapter 1) to accept a list of tab stops as arguments. Use the default
tab settings if there are no arguments.

I still have no idea what a tab stop is, but these methods can definitely
accept them. This could use some work, but I'm moving on.
*/

void entab(char[], char[], int);
int sequence(char[], int, char);
void detab(char[], char[], int);
void print(char[]);

int main() {
    char args[100] = "hello there, my name is jacob!";
    char delims[2] = " ";
    char **tokens = tokenize(args, delims);
    return 0;
}

/**
Entabs the given char array by inserting tabs at appropriate locations.
These tabs are inserted in the place of a specified number of spaces,
defined by the preprocessor variable SPACES.
*/
void entab(char sen[], char stops[], int len) {
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
Replaces the tabs in the given string with an equivalent number
of spaces. One tab stop is equal to 4 spaces.

This method changes the original array, and needs memory
for spaces to be appended. It will assume that the given char[]
has allocated space for this.
*/
void detab(char sen[], char stops[], int len) {
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
