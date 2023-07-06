#include <stdio.h>

enum BOOLEAN_VALUES {NO = 3, YES = 4};
enum escapes { BELL = '\a', BACKSPACE = '\b'};

int main() {
    int n = NO;
    int y = YES;
    printf("%d %d\n", n, y);
    char b = BELL;
    char ba = BACKSPACE;
    printf("%d %d\n", b, ba);

    // const mes[100]; cant have it's values modified.
    char mes[100];
    mes[0] = 'a';
    printf("%c\n", mes[0]);
    return 0;
}
