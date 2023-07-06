#include <stdio.h>

#define CHAR_SET "0123456789abcdef"

void reverse(char[]);
void itoa(int, char[]);
void itoa2(int, char[], int);

/**
Write a version of itoa that accepts three arguments instead of two.
The third argument is a minimum field width; the converted number must
be padded with blanks on the left if necessary to make it wide enough.
*/

int main() {
    char s[100];
    int i = 14;
    itoa2(i, s, 4);
    printf("%d -> '%s'\n", i, s);
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
Version of itoa that takes a width for the resulting string,
to be appended with spaces if necessary.
*/
void itoa2(int n, char s[], int w) {
    int i = 0, h;
    unsigned e = (unsigned) n;

    do {
        s[i++] = e % 10 + '0';
    } while ((e /= 10) > 0);

    if (n < 0)
        s[i++] = '-';

    for (h = 0; h < w - i + 1; h++)
        s[i++] = ' ';

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
