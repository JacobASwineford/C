#include <stdio.h>

/**
Verify that the expression getchar() != EOF is 0 or 1.
*/

int main() {
    int c = getchar();
    printf("%c %d", c, c != EOF);
    return 0;
}
