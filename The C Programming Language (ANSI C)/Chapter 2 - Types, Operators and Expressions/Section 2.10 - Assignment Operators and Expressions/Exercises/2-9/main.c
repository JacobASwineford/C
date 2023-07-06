#include <stdio.h>

int bitcount(unsigned);
int bitcount2(unsigned);

/**
In a two's complement number system, x &= (x - 1) deletes the rightmost
1-bit in x. Explain why. Use this observation to write a faster version
of bitcount.

suppose we have two bit strings, with the first one being x and the second being
x - 1:

101101
101100

notice that the first bit of the x - 1 is 0, and the first is 1. if we & these numbers,
we get the resulting bit string 101100 because the rightmost 1-bit was deleted.
This also works for even numbers:

101100
101011

which results in 101000, where the rightmost 1-bit is deleted.
*/

int main() {
    unsigned num = 1111111;
    int i = bitcount(num);
    printf("bitcount is %d\n", i);
    int e = bitcount2(num);
    printf("bitcount is %d\n", e);
    return 0;
}

/* bitcount: counts 1 bits in x */
int bitcount(unsigned x) {
    int b;

    for (b = 0; x != 0; x>>= 1)
        if (x & 01)
            b++;
    return b;
}

int bitcount2(unsigned x) {
    int b;

    for (b = 0; x != 0; x &= x - 1)
        b++;
    return b;
}
