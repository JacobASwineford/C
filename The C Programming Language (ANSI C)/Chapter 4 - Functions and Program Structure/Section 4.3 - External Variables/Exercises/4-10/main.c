#include <stdio.h>
#include <stdlib.h> /* for atof */
#include <math.h>

#define MAXOP 100 /* max size of operator or operand */
#define NUMBER '0' /* signal that a number was found */
#define VARIABLES 26 // number of variables that can be currently handled
#define VARIABLE 'v' // signal that a variable was found
#define LINE 200 // max line length
#define TOK 100 // maximum token length

int getop2(char[]);
void push(double);
double pop(void);
double peek(void);
void clear(void);

int add_variable(int);
void getline(void);
int gettok(int);

/**
An alternate organization uses getline() to read an entire
input line; this makes getch() and ungetch() unnecessary.
Revise the calculator to use this approach.

Its not exactly perfected, but I don't want to work on this anymore.
*/

double hvars[VARIABLES];
double vars[VARIABLES];
char pc;
char line[LINE];
char tok[TOK];

/* reverse polish calculator */
int main() {
    int type, in;
    double re, t, op, op2;

    int ie;
    for (ie = 0; ie < VARIABLES; ie++)
        hvars[ie] = 0;

    int pf = 0;
    while (1) {
        getline();
        in = 0;
        while (1) {
            in = gettok(in);
            type = getop2(tok);

            //printf("tok: %s, type: %d\n", tok, type);

            if (pf) {
                pf = 0;
                continue;
            }

            switch (type) {
                case NUMBER:
                    push(atof(tok));
                    break;
                case VARIABLE:
                    push(vars[pc - 'a']);
                    break;
                case '+':
                    op = pop();
                    op2 = pop();
                    op = op + op2;
                    printf("\t%.2f\n", op);
                    re = op;
                    push(op);
                    break;
                case '*':
                    op = pop();
                    op2 = pop();
                    op = op * op2;
                    printf("\t%.2f\n", op);
                    re = op;
                    push(op);
                    break;
                case '-':
                    op = pop();
                    op2 = pop();
                    op = op - op2;
                    printf("\t%.2f\n", op);
                    re = op;
                    push(op);
                    break;
                case '/':
                    op = pop();
                    op2 = pop();
                    if (op2 != 0) {
                        op = op / op2;
                        printf("\t%.2f\n", op);
                        re = op;
                        push(op);
                    }
                    break;
                case '%':
                    op = pop();
                    op2 = pop();
                    if ((int) op2 != 0) {
                        op = (int) op % (int) op2;
                        printf("\t%.2f\n", op);
                        re = op;
                        push(op); // cannot use modulo with double numbers.
                    }
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
                    add_variable(line);
                    pf = 1;
                    break;
                case 'r': // print the most recent variable
                    printf("\tThe most recently printed variable was %.1f.\n", re);
                    pf = 1;
                    break;
                default:
                    printf("error: unknown command %s\n", tok);
            }

            if (line[in] == '\0')
                break;
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
int add_variable(int in) {
    in = gettok(in);
    int var = getop2(tok) - 'a';
    printf("var is %d\n", var);
    in = gettok(in);
    printf("the value of s is '%s'\n", tok);
    vars[var] = atof(tok);
    hvars[var] = 1;
    return in;
}

/**
New version of getop to use with getline() and gettok(). This method
will now assume that a token is put into tok, and this token is trimmed.
*/
int getop2(char s[]) {
    int c = s[0], n = s[1];

    if (islower(c) && hvars[c - 'a'] == 1) {
        pc = c;
        return VARIABLE;
    }

    if (c == '-' && !isdigit(n))
        return '-'; // subtraction sign, not negative sign

    if (!isdigit(c) && c != '-')
        return c; /* not a number */

    return NUMBER;
}

/**
Reads a line of input into the global line variable.
*/
void getline() {
    int c, i = 0;
    c = getchar();
    while (c != '\n') {
        line[i++] = c;
        c = getchar();
    }
    line[i] = '\0';
}

/**
Reads the next token from the global line variable
into the global tok variable, starting from index.
returns the index of the last read character.

Generally speaking, the index returned from this method
can be used for feeding into the next token.
*/
int gettok(int li) {
    int c, ti = 0;

    if (line[li] == '\0')
        return li;

    c = line[li];
    while (isspace(c))
        c = line[++li];

    while (!isspace(c) && c != '\0') {
        tok[ti++] = c;
        c = line[++li];
    }
    tok[ti] = '\0';

    while (isspace(c))
        c = line[++li];
    return li;
}
