#include <stdio.h>

int lower(int);
int lower2(int);

/**
Rewrite the function lower, which converts upper case letters
to lower case, with a conditional expression instead of if-else.
*/

int main() {
    printf("%c\n", lower2('C'));
    return 0;
}

/* lower: convert c to lower case; ASCII only. */
int lower(int c) {
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else
        return c;
}

/**
Converts c to lower case, using a conditional expression.
ASCII only.
*/
int lower2(int c) {
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
