#include <stdio.h>

int power(int m, int n);

int main() {
    int base = 2;
    int to = 5;
    int p = power(base, to);
    printf("power: %d, %d, %d\n", base, to, p);

    return 0;
}

/**
Power: raise base to the n-th power: n>=0, version 3.
*/
int power(int base, int n) {
    int p;

    for (p = 1; n > 0; --n)
        p = p * base;
    return p;
}
