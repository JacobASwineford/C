#include <stdio.h>

#define BASE_SET "0123456789abcdef"
#define UNSIGNED_SIZE 32

void bprint(unsigned, int, int);
void rprint(char[], int);
unsigned getbits(unsigned, int, int);
unsigned invert(unsigned, int, int);

/**
Write a function invert(x,p,n) that returns x with the n bits
that begin a position p inverted (i.e. 1 changed into 0 and vice versa),
leaving the others unchanged.
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
Rotates x to the right n positions. positions higher than
the bitsize of unsigned (32 bits on my machine) are supported.
However, the UNSIGNED_SIZE number is currently defined by the symbolic constant
and may need to be changed manually.
*/
unsigned rightrot(unsigned x, int n) {
    /*
    bprint(x, 2, 32);
    int nn = n % UNSIGNED_SIZE;
    unsigned be = getbits(x, nn - 1, nn);
    unsigned right = x >> n;
    unsigned left = be << UNSIGNED_SIZE - nn;
    unsigned fin = left + right;
    bprint(be, 2, 32);
    bprint(right, 2, 32);
    bprint(left, 2, 32);
    bprint(fin, 2, 32);
    */
    int nn = n % UNSIGNED_SIZE;
    return (x >> n) + (getbits(x, nn - 1, nn) << UNSIGNED_SIZE - nn);
}
