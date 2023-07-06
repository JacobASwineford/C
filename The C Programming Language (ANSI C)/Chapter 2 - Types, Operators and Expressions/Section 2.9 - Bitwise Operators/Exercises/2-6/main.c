#include <stdio.h>

#define BASE_SET "0123456789abcdef"

void bprint(unsigned, int, int);
void rprint(char[], int);
unsigned getbits(unsigned, int, int);
unsigned setbits(unsigned, int, int, unsigned);

/**
Write a function setbits(x,p,n,y) that returns x with the n
bits that begin at position p set to the rightmost n bits of y,
leaving the other bits unchanged.
*/

int main() {
    int num = 11111111;
    return 0;
}

/**
Prints a base-10 number in a different base.
the given base has to be a viable index
within BASE_SET.

the resulting base number may by extended
by adding following 0's. This will not occur if
the resulting base-x string does not require
following 0s to get to or exceed the desired length.
*/
void bprint(unsigned num, int base, int to) {
    int i = 0;
    char arr[100];
    while (num) {
        arr[i++] = BASE_SET[num % base];
        num /= base;
    }
    int e = to - i;
    while (e-- > 0)
        arr[i++] = BASE_SET[0];
    rprint(arr, i - 1);
}

/**
Prints the given array, from the given index,
in the reverse order.
*/
void rprint(char arr[], int from) {
    while (from >= 0)
        printf("%c", arr[from--]);
    printf("\n");
}

/* getbits: gets n bits from position p */
unsigned getbits(unsigned x, int p, int n) {
    return (x >> (p + 1 - n)) & ~(~0 << n);
}

/**
gets the n bits at position p from x and assigns them to the
beginning of y, leaving the other bits unchanged.
*/
unsigned setbits(unsigned x, int p, int n, unsigned y) {
    /*
    int b = getbits(x, p, n);
    unsigned int mask = ~0 << n;
    unsigned next = y & mask;
    unsigned fin = next ^ b;
    bprint(x, 2, 32);
    bprint(b, 2, 32);
    bprint(mask, 2, 32);
    bprint(y, 2, 32);
    bprint(next, 2, 32);
    bprint(fin, 2, 32);
    */
    return (y & (~0 << n)) ^ getbits(x, p, n);
}
