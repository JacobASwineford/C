#include <stdio.h>

#define BASE_SET "0123456789abcdef"

void bprint(unsigned, int, int);
void rprint(char[], int);
unsigned getbits(unsigned, int, int);
unsigned invert(unsigned, int, int);

/**
Write a function rightrot(x,n) that returns the value of the integer
x rotated to the right by n bit positions.
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
inverts n bits from x, beginning from position p, leaving
the other bits unchanged.
*/
unsigned invert(unsigned x, int p, int n) {
    /*
    bprint(x, 2, 32);
    unsigned bitmask = ~(~0 << n) << p - n + 1;
    unsigned a = x ^ bitmask;
    bprint(bitmask, 2, 32);
    bprint(a, 2, 32);
    */
    return x ^ (~(~0 << n) << p - n + 1);
}
