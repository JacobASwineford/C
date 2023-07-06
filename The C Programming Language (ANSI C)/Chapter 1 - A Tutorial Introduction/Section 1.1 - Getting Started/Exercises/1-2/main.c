#include <stdio.h>

/**
Experiment to find out what happens when printf's argument
string contains a \c, where c is some character not listed above - (\t, \n, \", \\).

FULL LIST IN SECTION 2.3
*/

int main() {
    printf("hello, world!\c");

    return 0;
}
