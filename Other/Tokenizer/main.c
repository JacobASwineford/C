#include <stdio.h>
#include <string.h>

char **tokenize(char*, char*);
int tokens(char*, char*);
int in(char, char*);

void *alloc(int);

#define MAXTOKLEN 100

/**
Splits a string into tokens based on the given set of delimiters,
and returns references to those tokens. The tokens are copied
into statically allocated memory.
*/
char **tokenize(char *str, char *delims) {
    char **toks = alloc((sizeof(char*) * (tokens(str, delims) + 1)));
    char buf[MAXTOKLEN];
    char *bufp = buf;
    int i, inside = 0, tokens = 0;
    void *cpy;
    while (1) {
        i = in(*str, delims);

        if (i && !inside) {
            str++;
            continue;
        }

        if (i || (inside && !*str)) {
            *bufp = '\0';
            cpy = alloc(bufp - buf + 1);
            strcpy(cpy, buf);
            *(toks + tokens) = cpy;
            tokens++;
            inside = 0;
            bufp = buf;
        } else {
            inside = 1;
            *bufp = *str;
            bufp++;
        }

        if (!*str)
            break;
        str++;
    }

    *(toks + tokens) = 0; // null
    return toks;
}

/**
Returns the number of tokens in a string, based on the given
set of delimiters.
*/
int tokens(char *str, char *delims) {
    int inside = 0, i, tokens = 0;
    while (*str) {
        i = in(*str, delims);

        // if there is currently no token and the character is in the set of delimiters,
        // then skip this character.
        if (i && !inside) {
            str++;
            continue;
        }

        // otherwise, we are in a token
        if (i) {
            tokens++;
            inside = 0;
        } else
            inside = 1;
        str++;
    }

    return (inside) ? ++tokens : tokens;
}

/**
Returns whether a character is present in a string or not.
*/
int in(char c, char *str) {
    while (*str) {
        if (*str == c)
            return 1;
        str++;
    }
    return 0;
}

/* ########################################### */

#define MAXALLOC 2000

char allocbuf[MAXALLOC];
char *allocp = allocbuf;

/**
Allocates a particular amount of bytes from statically allocated
memory.
*/
void *alloc(int bytes) {
    int max = allocbuf + MAXALLOC;
    int next = allocp + bytes;
    if (next > max)
        return NULL;

    void *ret = allocp;
    allocp += bytes;
    return ret;
}


