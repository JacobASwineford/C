#include <stdio.h>

int bitcount(unsigned);

int main() {
    unsigned num = 1111111;
    int i = bitcount(num);
    printf("bitcount is %d\n", i);
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

