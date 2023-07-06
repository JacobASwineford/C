#include <stdio.h>
#include <ctype.h>

int getint(int*);
int getch(void);
void ungetch(int);

/**
As written, getint treats a + or - not followed by a digit as
a valid representation of 0. Fix it to push such a character
back on the input.
*/

int main() {
    int i = 24;
    getint(&i);
    printf("the value of i is %d.", i);
    return 0;
}

/**
Modified version of getint that accounts for sign characters
(+, -) that don't have an following digit as a valid representation
of 0. the sign is now pushed back on the input., and pn remains
unchanged.
*/
int getint(int *pn) {
    int c, n, sign;

    while (isspace(c = getch())); /* skip white space */

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* its's not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        n = getch();
        if (!isdigit(n)) {
            ungetch(c); // push back sign onto input
            return 0;
        }
        c = n; // otherwise, continue execution
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (possibly) pushed back character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back onto input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

