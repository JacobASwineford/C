#include "../../../../Tools/tokens.c";
#include <stdio.h>
#include <stdlib.h>

#define SPACES 4
#define LEN 50

/**
Extend entab and detab to accept the shorthand
entab -m +n
to mean tab stops every n columns, starting a column m.Choose
convenient (for the user) default behavior.

The logic behind this is as follows:
    Interpret optional arguments
    define stops given optional arguments
    use the correct function with the given stops
*/

void entab(char[], char[], int);
int sequence(char[], int, char);
void detab(char[], char[], int);
void print(char[]);
int *interpret(char**, int);

int main() {
    char args[100] = "entab -3 +6";
    char delims[2] = " ";
    int num_tokens = tokens(args, delims);
    char **token_array = tokenize(args, delims);

    if (strcmp(*token_array, "entab") == 0)
        printf("Entab!\n");
    else if (strcmp(*token_array, "detab") == 0)
        printf("Detab!\n");
    else {
        printf("Unknown command: %s\n", *token_array);
        return 0;
    }

    int *stops = interpret(token_array, num_tokens);
    printf("m = %d, n = %d\n", stops[0], stops[1]);

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

/**
Interprets the given arguments for the entab and detab functions.
Optional parameters -m and +n determine tab stops for entab and
detab, and is returned as an array of stops that should be passed to
the appropriate function. optional parameters should never be the first argument,
as this is the name of the function to run.
*/
int *interpret(char **tokens, int num_tokens) {
    if (num_tokens <= 1)
        return NULL;

    // optional parameter values, 0 means not included
    int m = 0, n = 0;

    // read in optional parameters
    int in = 1;
    char *tok = *(tokens + in);
    char c;
    while (tok) {
        // optional parameter parsing
        if (num_tokens >= in && strlen(tok) >= 2) {
            switch ( *(*(tokens + in)) ) {
            case '-': {
                m = atoi(tok + 1);
                break;
            }
            case '+': {
                n = atoi(tok + 1);
                break;
            }
            default:
                printf("Unknown argument: %s\n", tok);
            }
        } else
            printf("Unknown argument: %s\n", tok);
        tok = *(tokens + ++in);
    }

    int *stops = alloc(sizeof(int) * 2);
    *stops = m;
    *(stops + 1) = n;

    return stops;
}
