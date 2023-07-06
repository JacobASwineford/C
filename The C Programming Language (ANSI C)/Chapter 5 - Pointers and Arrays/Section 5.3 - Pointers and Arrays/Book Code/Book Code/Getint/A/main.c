#include <stdio.h> // not included in book, needed for EOF constant
#include <ctype.h>

int getint(int*);
int getch(void);
void ungetch(int);

int main() {

    return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn) {
    int c, sign;

    while (isspace(c = getch())); /* skip white space */

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* its's not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
}


/**
getch() and ungetch() not provided, but refer to the definitions
of theses functions from Section 4.3.
*/

int getch(void) {

}

void ungetch(int i) {

}
