#include <stdio.h>
#include <string.h>

int strindex(char[], char[]);
int strrindex(char[], char[]);

/**
Write a function strrindex(s, t) which returns the position
of the rightmost occurrence of t in s, or -1 if there is none.
*/

int main() {
    char s[100] = "hi, hi!";
    char t[3] = "hi";
    int f = strindex(s, t);
    int l = strrindex(s, t);
    printf("The first and last occurrences of '%s' are at %d and %d.\n", t, f, l);
    return 0;
}

/* strindex: return index of t in s, -1 if none */
int strindex(char s[], char t[]) {
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++) {
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++);
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

/**
Returns the rightmost index of t in s, or -1 if there
is no occurrence.
*/
int strrindex(char s[], char t[]) {
    int i, j, k;

    for (i = strlen(s) - 1; i >= 0; i--) {
        for (j = i, k = 0; t[k] != '\0' && s[j]==t[k]; j++, k++);
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

