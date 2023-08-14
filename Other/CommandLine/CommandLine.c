#include "../../testheaders.c"
#include "../Tokenizer/main.c"

#define BUF_SIZE 100

/**
* Command Line that can execute basic commands.
*/
int main() {
    printf("Welcome to the command line!\n\n");
    char buf[BUF_SIZE];
    char **tokens;
    char *token;
    int i = 0;
    while (1) {
        printf("-> ");
        fgets(buf, BUF_SIZE, stdin);
        tokens = tokenize(buf, " ");
        token = *tokens;
        while (token) {
            printf("token %d: %s\n", i++, token);
            token = *(tokens + i);
        }
        i = 0;

        if (fork() == 0)
            execvp(*tokens, tokens);
    }

    return 0;
}
