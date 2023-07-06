#include <stdio.h>

void reverse(char[]);
void itoa(int, char[]);

int main() {

    return 0;
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[]) {
    int i, sign;

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
