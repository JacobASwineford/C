#include "../../../../Tools/tokens.c";
#include <stdio.h>
#include <string.h>

#define INTEGER 1
#define OPERATOR 2

int read(char**, int);

void push(int);
int pop();

void print(int*, int len);

/**
Write the program expr, which evaluates a reverse polish
expression from the command line, where each operator
or operand is a separate argument. For example:
    expr 2 3 4 + *
evaluates 2 * (3 + 4).

For the sake of simplicity, I'm going to assume that
everything entered is an integer or operator (*, /, +, -);
*/
int main() {
    char args[100] = "2 3 4 + *";
    char delims[2] = " ";
    int numtok = tokens(args, delims);
    char **tokens = tokenize(args, delims);

    int status, index = 0;
    int right = 0, left = 0, ans;
    while (numtok--) {
        status = read(tokens, index);
        if (status == INTEGER) {
            push(atoi(*(tokens + index)));
        } else if (strcmp(tokens[index], "+") == 0) {
            right = pop();
            left = pop();
            ans = left + right;
            printf("%d + %d = %d\n", left, right, ans);
            push(ans);
        } else if (strcmp(tokens[index], "-") == 0) {
            right = pop();
            left = pop();
            ans = left - right;
            printf("%d - %d = %d\n", left, right, ans);
            push(ans);
        } else if (strcmp(tokens[index], "*") == 0) {
            right = pop();
            left = pop();
            ans = left * right;
            printf("%d * %d = %d\n", left, right, ans);
            push(ans);
        } else if (strcmp(tokens[index], "/") == 0) {
            right = pop();
            left = pop();
            ans = left / right;
            printf("%d / %d = %d\n", left, right, ans);
            push(ans);
        } else {
            printf("Unknown operator: '%s'\n", tokens[index]);
        }
        index++;
    }

    return 0;
}

/**
Reads and returns the type of value that the argument
at index is, within argv.
*/
int read(char **argv, int index) {
    if (atoi(*(argv + index)) == 0 && strcmp(*(argv + index), "0") != 0)
        return OPERATOR;
    return INTEGER;
}

#define MAXSTACK 100

int stack[MAXSTACK];
int *stackp = stack;

/**
Pushes a string onto the stack.
*/
void push(int val) {
    int max = stack + MAXSTACK;
    if (stackp < max) {
        *stackp = val;
        stackp++;
    }
    else
        printf("No more room in stack.\n");
}

/**
pops the character off of the stack, effectively removing it.
*/
int pop() {
    int ret;
    if (stack - stackp != 0) {
        ret = *(stackp - 1);
        stackp--;
    } else {
        ret = NULL; // also 0, could cause confusion
        printf("Nothing in the stack to pop.\n");
    }
    return ret;
}

