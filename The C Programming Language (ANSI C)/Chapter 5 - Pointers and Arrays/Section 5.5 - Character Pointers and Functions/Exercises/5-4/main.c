#include <stdio.h>
#include <string.h>

/**
Write the function stdend(s, t), which returns 1 if the string
t occurs at the end of the string s, 0 otherwise.
*/

int strend(char*, char*);

int main() {
    int i = strend("fleop", "fleop");
    printf("%d\n", i);
    return 0;
}

/**
Tests to see if the string t occurs at the end of string s.
if so, this method returns 1. 0 if it does not occur.
*/
int strend(char *s, char *t) {
    if (s == '\0' || t == '\0')
        return 0;

    int tlen = strlen(t);
    int slen = strlen(s);

    if (tlen > slen)
        return 0;

    s += slen - 1;
    t += tlen - 1;

    while (*s == *t) {
        s--;
        t--;
        if (--tlen <= 0)
            return 1;
    }

    return 0;
}

