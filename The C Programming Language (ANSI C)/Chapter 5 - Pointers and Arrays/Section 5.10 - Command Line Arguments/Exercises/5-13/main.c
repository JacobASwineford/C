#include "../../../../Tools/tokens.c";
#include <stdio.h>
#include <stdlib.h>

/**
Write the program tail, which prints the last n lines of its input.
By default, n is 10, let us say, but can changed by an optional
argument, so that
tail -n
prints the last n lines. The program should behave rationally
no matter how unreasonable the input or value of n. Write the program so
that it m akes the best use of available storage; lines should be stored
as in the sorting program of Section 5.6, not in a two dimensional array of
fixed size.

With tokenize and alloc, this is a very simple process where the value of n
is gotten from arguments to this program and only some tokens are printed
from the tokenized lines. The storage problem is also sorted out dynamically
by alloc within tokenize.
*/

void interpret(char**, char**);

int n = 10; // print the last n lines

int main() {
    char sen[100] = "hello\nthere\nnice\nto\nmeet\nyou.";
    char args[50] = "tail -4";
    char delims[2] = " ";
    char **tokens = tokenize(args, delims);
    char **sen_tokens = tokenize(sen, "\n");
    interpret(tokens, sen_tokens);

    // set the index and pointed token to the end
    int in = 0;
    char *tok = *sen_tokens;
    while (tok)
        tok = *(sen_tokens + ++in);
    tok = *(sen_tokens + --in);

    // crawl backwards and print based off of n
    while (n) {
        printf("%s ", tok);
        tok = *(sen_tokens + --in);
        n--;
    }

    return 0;
}

/**
Interprets the given arguments and sets the value of this programs
flags accordingly. This program has the flag -n, where n represents the
number of lies that are to be printed from the last line backward. This method
already assumes that the first token is "tail" for calling this program.
*/
void interpret(char **tokens, char **sen_tokens) {
    int in = 1;
    char *tok = *(tokens + in);
    while (tok) {
        if (strlen(tok) >= 2 && *tok == '-')
                n = atoi(tok + 1);
        else
            printf("Unknown argument: '%s'\n", tok);
        tok = *(tokens + ++in);
    }

    // count the number of tokens in the sentence, and use that
    // to adjust n as needed
    tok = *sen_tokens;
    in = 0;
    while (tok)
        tok = *(sen_tokens + ++in);

    if (n > in || n < 0)
        n = in;
}
