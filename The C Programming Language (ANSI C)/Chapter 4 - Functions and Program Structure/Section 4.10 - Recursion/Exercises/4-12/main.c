#include <stdio.h>

/**
Adapt the ideas of printd to write a recursive version
of itoa; that is, convert an integer into a string
by calling a recursive routine.
*/

void itoa(char[], int);
void printd(int);
void print(char[]);

int main() {
    int i = 123456;
    char buf[100];
    //printd(i);
    itoa(buf, i);
    print(buf);
    return 0;
}

/**
Writes the given integer into the given buffer.
*/
void itoa(char buf[], int n) {
    static int bptr = 0;
    if (n < 0) {
        buf[bptr++] = '-';
        n = -n;
    }
    if (n / 10)
        itoa(buf, n / 10);
    buf[bptr++] = n % 10 + '0';
    buf[bptr + 1] = '\0';
}

/* print n in decimal */
void printd(int n) {
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10)
        printd(n / 10);
    putchar(n % 10 + '0');
}

void print(char arr[]) {
    putchar('[');
    int i = 0, c;
    while ((c = arr[i++]) != '\0') {
        if (arr[i] == '\0')
            printf("%c", c);
        else
            printf("%c, ", c);
    }
    printf("]\n");
}
