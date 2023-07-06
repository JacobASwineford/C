#include <stdio.h>
#include <stdlib.h> /* for atof */
#include <math.h>

#define MAXOP 100 /* max size of operator or operand */
#define NUMBER '0' /* signal that a number was found */
#define VARIABLES 26 // number of variables that can be currently handled
#define VARIABLE 'v' // signal that a variable was found

int getop(char[]);
void push(double);
double pop(void);
double peek(void);
void clear(void);

void add_variable(char[]);

/**
Modify getop so that it doesn't need to use
ungetch(). Hint: use an internal static variable.

Just as a note to the reader, this is built in the code made in
exercise 4-6, where I was tasked with adding variables for this
calculator.
*/

double hvars[VARIABLES];
double vars[VARIABLES];
char pc;

/* reverse polish calculator */
int main() {
    int type;
    double op2;
    char s[MAXOP];
    double t;
    double re;

    int i;
    for (i = 0; i < VARIABLES; i++)
        hvars[i] = 0;

    int pf = 0;
    while ((type = getop(s)) != EOF) {
        if (pf) {
            pf = 0;
            continue;
        }

        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case VARIABLE:
            push(vars[pc - 'a']);
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
            re = pop();
            printf("\t%.8g\n", re);
            break;
        case 't': // t for top
            t = peek();
            if (t != 0.0)
                printf("\tThe top element of the stack is %.1f.\n", t);
            else
                printf("\tThere are no elements in the stack.\n");
            pf = 1;
            break;
        case 'p': // prints the stack
            print_stack();
            pf = 1;
            break;
        case 's': // swaps the first two elements of the stack
            swap_top();
            pf = 1;
            break;
        case 'c': // clears the stack
            clear();
            pf = 1;
            break;
        case '&': // assign valid variables a value
            add_variable(s);
            pf = 1;
            break;
        case 'r': // print the most recent variable
            printf("\tThe most recently printed variable was %.1f.\n", re);
            pf = 1;
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

/**
Returns the top element of the stack without popping.
*/
double peek() {
    if (sp != 0)
        return val[sp - 1];
    else
        return 0.0;
}

/**
prints the values in the stack in the format [..., ..., ...]
*/
void print_stack() {
    printf("\t[");
    int i;
    for (i = 0; i < sp; i++) {
        if (i == sp - 1)
            printf("%.1f", val[i]);
        else
            printf("%.1f, ", val[i]);
    }
    printf("]\n");

}

/**
Swaps the first two elements in the stack, if possible.
*/
void swap_top() {
    double t;
    if (sp >= 2) {
        t = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = t;
    } else {
        printf("\tThere are only %d element(s) in the stack. At least two are needed.\n", sp);
    }
}

/**
clears the stack.
*/
void clear() {
    sp = 0;
}

/**
Assign a variable a value. variables are single letters, ranging from a to z.
*/
void add_variable(char s[]) {
    int var = getop(s) - 'a';
    printf("var is %d\n", var);
    getop(s);
    printf("the value of s is '%s'\n", s);
    vars[var] = atof(s);
    hvars[var] = 1;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, c, t;
    static int un;
    static int hun = 0;

    while (1) {
        if (hun) {
            c = un;
            hun = 0;
        } else
            c = getchar();
        s[0] = c;
        if (c != ' ' && c != '\t')
            break;
    }

    // handle valid variable names
    if (islower(c) && hvars[c - 'a'] == 1) {
        pc = c;
        return VARIABLE;
    }

    // handle not a number
    if (!isdigit(c) && c != '.' && c != '-')
        return c; // not a number

    // handle subtraction sign
    i = 0;
    t = c;
    if (hun) {
        c = un;
        hun = 0;
    } else
        c = getchar();
    if (!isdigit(c) && t == '-') {
        un = c;
        hun = 1;
        return t;
    }

    // collect integer part
    while (isdigit(c)) {
        s[++i] = c;
        if (hun) {
            c = un;
            hun = 0;
        } else
            c = getchar();
    }

    // collect decimal part, if any
    if (c == '.') {
        s[++i] = c;
        if (hun) {
            c = un;
            hun = 0;
        } else
            c = getchar();
        while (isdigit(c)) {
            s[++i] = c;
            if (hun) {
                c = un;
                hun = 0;
            } else
                c = getchar();
        }
    }

    s[++i] = '\0';
    if (c != EOF) {
        un = c;
        hun = 1;
    }
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
