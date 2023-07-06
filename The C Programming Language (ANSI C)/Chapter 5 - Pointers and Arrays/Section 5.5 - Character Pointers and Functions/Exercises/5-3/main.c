#include <stdio.h>

void strcat(char[], char[]);
void strcat2(char*, char*);

/**
Write a pointer version of the function strcat that we
showed in chapter 2: strcat(s, t) copies the string t
to the end of s.
*/

int main() {
    char s[100] = "Hi there, my name is Jacob.";
    strcat2(&s, " Nice to meet you.");
    printf("'%s'\n", s);
    return 0;
}

/* concatenate t to the end of s; s must be big enough */
void strcat(char s[], char t[]) {
    int i, j;

    i = j = 0;
    while (s[i] != '\0')
        i++;
    while ((s[i++] = t[j++]) != 0);
}

/**
concatenates t to the end of s. pointer version.
*/
void strcat2(char *s, char *t) {
    while (*s) s++;
    while (*s++ = *t++);
}
