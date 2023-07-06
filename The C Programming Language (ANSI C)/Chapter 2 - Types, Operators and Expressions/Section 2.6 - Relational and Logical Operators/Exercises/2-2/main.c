#include <stdio.h>

/**
for (i = 0; i < lim-1 && (c = getchar()) != '\n' && c != EOF; ++i)
        s[i] = c;

Write a loop equivalent to the for loop above without using
&& or ||.
*/

int main() {
    int i, lim = 100, s[lim];
    char c;

    for (i = 0; i < lim - 1; ++i) {
        c = getchar();
        if (c == '\n') break;
        if (c == EOF) break;
        s[i] = c;
    }

    return 0;
}
