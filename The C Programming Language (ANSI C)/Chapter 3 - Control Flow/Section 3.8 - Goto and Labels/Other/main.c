#include <stdio.h>

/**
An interesting observation about goto statements is that they
are executed in normal sequential order, and are not skipped in
the process despite being a separate block of code.
*/

int main() {
    int flag = 0;

    statement: {
        printf("Statement!\n");
        flag =  1;
    }

    printf("hi there!\n");
    printf("sup!\n");

    goto statement;

    return 0;
}
