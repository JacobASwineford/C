#include <stdio.h>
#include <math.h>

#define BASE_SET "0123456789abcdef"
#define UNSIGNED_SIZE 32

void bprint(unsigned, int, int);
void rprint(char[], int);
unsigned getbits(unsigned, int, int);
unsigned setbits(unsigned, int, int, unsigned);
unsigned invert(unsigned, int, int);
unsigned rightrot(unsigned, int);

int main() {
    unsigned num = 1122334455;
    bprint(num, 2, 32);
    bprint(num, 16, 0);
    return 0;
}

/**
Prints a base-10 number in a different base.
the given base has to be a viable index
within BASE_SET.

the resulting base number may by extended
by adding following 0's (more specifically, BASE_SET[0]).
This will not occur if the resulting base-x string does not require
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

unsigned getbits(unsigned x, int p, int n) {
    return (x >> (p + 1 - n)) & ~(~0 << n);
}

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

#define val 100


