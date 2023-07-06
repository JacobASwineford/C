#include <stdio.h>

/**
Write a program to remove trailing blanks and tabs from each line of
input, and delete entirely blank lines.
*/

void trim(char sen[]);

int main() {
    char sen[100] = "hello there";
    btrim(sen);
    printf("%s\n", sen);


    return 0;
}

/**
Removes trailing blanks and tabs from the given string. the leftmost
significant character to the right gets copied over to the beginning
of the string.
*/
void btrim(char sen[]) {
    char c;
    int blo = 0;
    while (1) {
        c = sen[blo];
        if (c == ' ' || c == '\t')
            blo++;
        else
            break;
    }

    int s = 0;
    while (c) {
        c = sen[blo++];
        sen[s++] = c;
    }
}
