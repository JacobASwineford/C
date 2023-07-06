#include <stdio.h>
#define MAXLINE 200

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/**
Write a program to print all input lines that are longer than 80 characters.
*/

int main() {
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }

        if (len > 80)
            printf("The given sentence\n\n%s\n\nis longer than 80 characters\n", line);
        else
            printf("The given sentence\n\n%s\n\nis not longer than 80 characters\n", line);
    }
    if (max > 0)
        printf("%s", longest);

    return 0;
}

/**
getline: Read a line into s, return length.
*/
int getline(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/**
copy: copy 'from' into 'to'; assume to is big enough.
*/
void copy(char to[], char from[]) {
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
