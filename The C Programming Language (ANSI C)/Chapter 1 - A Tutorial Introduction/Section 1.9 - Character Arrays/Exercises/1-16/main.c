#include <stdio.h>
#define MAXLINE 10

int getline(char line[], int maxline);
int mgetline(char line[], int maxLine);
void copy(char to[], char from[]);

/**
Revise the main routine of the longest-line program so
it will correctly print the length of arbitrarily long input lines,
and as much as possible of the text.

Without modifying the getline function, the length of any given sentence
will be capped at MAXLINE (limit inside getline). This is also the case for
printing as much as possible of the text.
*/

int main() {
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = mgetline(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
        printf("Echoed: %s\n", line);
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
mgetline: Read a line into s, return the true length of the given
sentence. As much of the sentence as possible is copied into the given
character array.
*/
int mgetline(char s[], int lim) {
    int c, i;

    i = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        if (i < lim)
            s[i] = c;
        i++;
    }

    if (i >= lim)
        s[lim - 1] = '\0';
    else s[i] = '\0';
    printf("length: %d\n", i);

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
