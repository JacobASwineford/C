#include <stdio.h>
#include <stdlib.h> /* for atof */

#define MAXOP 100 /* max size of operator or operand */
#define NUMBER '0' /* signal that a number was found */

int getop(char[]);
void push(double);
double pop(void);

/**
Given the basic framework, it's straightforward to extend the
calculator. Add the modulus (%) operator and provisions for
negative numbers.
*/

/* reverse polish calculator */
int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0)
                push(pop() / op2);
            break;
        case '%':
            op2 = pop();
            if ((int) op2 != 0)
                push((int) pop() % (int) op2); // cannot use modulo with double numbers.
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
        }
    }
    return 0;
}

#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f into stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value of stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, c, t;

    while ((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
        return c; /* not a number */

    i = 0;
    t = c;
    c = getch();
    if (!isdigit(c) && t == '-') {
        ungetch(c);
        return t; // negation sign, not negative sign
    }


    // collect integer part
    while (isdigit(c)) {
        s[++i] = c;
        c = getch();
    }

    // collect decimal part, if any
    if (c == '.') {
        s[++i] = c;
        c = getch();
        while (isdigit(c)) {
            s[++i] = c;
            c = getch();
        }
    }

    s[++i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
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
