#include "../../../../Tools/tokens.c";
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to text lines */

// name needs to be changed, duplicate method in stdlib
void qsort2(void *lineptr[], int left, int right,
           int (*comp)(void *, void *));
int strcmp2(char *, char *);
int numcmp(char *, char *);

void interpret(char **);
void print(char **);

// flags
int r = 0;
int n = 0;

/**
Modify the sort program to handle the -r flag, which indicates sorting
in reverse (decreasing) order. Be sure that -r works with -n.

This whole program needs to be gutted and redone, because I don't
have a good way to use readlines, writelines, and argv. Thus, I will
use tokenize to simplify this process.

Something is off about the qsort algorithm. I don't really care to check,
that's not what this exercise is about.
*/

int main(int argc, char *argv[]) {
    char lines[100] = "Hello\nhow\nare\nyou\ntoday?";
    char line_delims[2] = "\n";
    char **line_toks = tokenize(lines, line_delims);
    int num_lines = tokens(lines, line_delims);

    char args[50] = "qsort";
    char args_delims[2] = " ";
    char **args_toks = tokenize(args, args_delims);

    interpret(args_toks); // set flags

    qsort2(line_toks, 0, num_lines - 1,
            (n) ? numcmp : strcmp2);

    print(line_toks);

    return 0;
}

/* qsort: sort v[last]...v[right] into increasing order */
void qsort2(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right) /* do nothing if the array contains */
        return; /* fewer than two elements */
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1, comp);
    qsort(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j) {
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#include <stdlib.h>

int strcmp2(char *s1, char *s2) {
    return (r) ? -strcmp(s1, s2) : strcmp(s1, s2);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2) {
    double v1, v2;
    int ret = 0;

    v1 = atof(s1);
    v2 = atof(s2);

    printf("%f %f\n", v1, v2);

    if (v1 < v2)
        ret = -1;
    else if (v1 > v2)
        ret = 1;
    else
        return 0;

    return (r) ? -ret : ret;
}

/**
Interprets the arguments and sets the following valid flags:
-r -> reverse sort
-n -> numeric sort
*/
void interpret(char **args_toks) {
    if (*args_toks == 0)
        return;
    int in = 1;
    char *tok = *(args_toks + in);

    while (tok) {
        if (strlen(tok) >= 2) {
            switch ( *(tok + 1) ) {
            case 'r':
                r = 1;
                break;
            case 'n':
                n = 1;
                break;
            default:
                printf("Unknown argument: %s\n", tok);
            }
        } else
            printf("Unknown argument: %s\n", tok);
        tok = *(args_toks + ++in);
    }
}

void print(char **toks) {
    int in = 0;
    char *tok = *toks;
    while (tok) {
        printf("-> %s\n", tok);
        tok = *(toks + ++in);
    }
}




