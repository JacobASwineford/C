#include <stdio.h>

/**
Write an alternate version of squeeze(s1,s2) that deletes
each character in s1 that matches any character in the string s2.
*/

void squeeze(char[], char[]);
int in(char, char[]);

int main() {
    char s[10] = "hithere";
    squeeze(s, "eh");
    printf("%s\n", s);

    return 0;
}

/**
Deletes all occurrences of all characters in s that are
also present in c.
*/
void squeeze(char s[], char c[]) {
    int i, j;

    for (i = j = 0; s[i] != '\0'; i++)
        if (!in(s[i], c))
            s[j++] = s[i];
    s[j] = '\0';
}

/**
Returns 1 if c is contained inside the given string.
*/
int in(char c, char s[]) {
    int i = 0;
    char cha;
    while ((cha = s[i++]) != '\0') {
        if (c == cha)
            return 1;
    }
    return 0;
}
