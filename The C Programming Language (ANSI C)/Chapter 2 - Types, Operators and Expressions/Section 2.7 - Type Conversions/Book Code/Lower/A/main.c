#include <stdio.h>

int lower(int);

int main() {
    int a = 'A';
    a = lower(a);
    printf("%c\n", a);
    return 0;
}

/* lower: convert c to lower case; ASCII only. */
int lower(int c) {
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else
        return c;
}
