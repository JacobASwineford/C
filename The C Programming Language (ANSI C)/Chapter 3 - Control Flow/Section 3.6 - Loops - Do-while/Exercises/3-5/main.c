#include <stdio.h>

#define CHAR_SET "0123456789abcdef"

void reverse(char[]);
void itoa(int, char[]);
void itob(int, char[], int);

/**
Write a function itob(n,s,b) that converts the integer n
into a base b character representation in the string s. In particular,
itob(n, s, 16) formats as a hexadecimal integer in s.
*/

int main() {
    char s[100];
    int i = -339594944;
    itob(i, s, 16);
    printf("%d -> %s\n", i, s);
    return 0;
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[]) {
    int i, sign, e;

    if ((sign = n) < 0) /* record sign */
        n = -n; /* make n positive */
    i = 0;
    do { /* generate digits in reverse order */
        s[i++] = n % 10 + '0'; /* get next digit */
    } while ((n /= 10) > 0); /* delete it */

    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s); // reverse is not provided, but part of the algorithm
}

/**
converts the given integer into the specified base-string.
*/
void itob(int n, char s[], int b) {
    int i = 0;
    unsigned e = (unsigned) n;

    do {
        s[i++] = CHAR_SET[e % b];
    } while ((e /= b) > 0);

    if (n < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/**
Reverses the given string in-place.
*/
void reverse(char s[]) {
    int b = 0, e = strlen(s) - 1, t;
    while (b < e) {
        t = s[b];
        s[b] = s[e];
        s[e] = t;
        b++;
        e--;
    }
}
