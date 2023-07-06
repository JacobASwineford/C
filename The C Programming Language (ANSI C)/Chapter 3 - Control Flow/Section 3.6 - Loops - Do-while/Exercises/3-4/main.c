#include <stdio.h>

void reverse(char[]);
void itoa(int, char[]);
void itoa2(int, char[]);

/**
In a two's complement number representation, our version
of itoa does not handle the largest negative number, that is,
the value of n equal to -(2^worldsize - 1). Explain why not.
Modify it to print that value correctly, regardless on the machine
on which it runs.

The reason that the largest negative number is not handled is because
on a twos complement system the inverse of the max negative value
is still the negative value. here is an example for 8 bit arithmetic:

10000000
flipped, add 1:
01111111 + 1 ->
10000000

when twos complement is applied to make the number negative, the result
is the same number in the system. Therefore, to fix this problem the feed
number must be cast to unsigned, with the sign previously calculated
and appended to the given char[].
*/

int main() {
    char arr[100];
    char arr2[100];
    itoa(-2147483648, arr);
    printf("%s {'(' = 40}\n", arr);
    itoa2(-2147483648, arr2);
    printf("%s\n", arr2);
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
Version of itoa that handles the largest negative integer.
*/
void itoa2(int n, char s[]) {
    int i;
    unsigned e = (unsigned) n;
    i = 0;
    do {
        s[i++] = e % 10 + '0';
    } while ((e /= 10) > 0);

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
