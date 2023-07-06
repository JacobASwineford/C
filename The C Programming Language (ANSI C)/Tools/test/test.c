#include "../tokens.c";
#include <stdio.h>

int main() {
    char sentence[100] = "Understanding the importance of programming languages";
    char delims[3] = " ";
    char **tokens = tokenize(sentence, delims);

    int i = 0;
    char *tok = *(tokens + i);
    while (tok) {
        printf("%s\n", tok);
        tok = *(tokens + ++i);
    }


    return 0;
}
