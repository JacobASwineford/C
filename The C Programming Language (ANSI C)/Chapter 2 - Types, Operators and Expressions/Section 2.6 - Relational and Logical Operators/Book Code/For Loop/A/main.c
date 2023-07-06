#include <stdio.h>

int main() {
    // added to make the program compilable
    int lim = 100;
    int s[lim];
    int i;
    char c;

    for (i = 0; i < lim-1 && (c = getchar()) != '\n' && c != EOF; ++i)
        s[i] = c;
    return 0;
}
