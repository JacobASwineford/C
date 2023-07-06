#include <stdio.h>

void escape(char[], char[]);
void descape(char[], char[]);

/**
Write a function escape(s,t) that converts characters
like newline and tab into viable escape sequences like
\n and \t as it copies the string t to s. Use a switch.
Write a function for the other direction as well,
converting escape sequences into real characters.
*/

int main() {
    char sen[100] = "Hi\tthere\t,\nmy name is Jacob!";
    char to[150];
    printf("%s\n\n", sen);
    escape(to, sen);
    printf("%s\n\n", to);
    descape(to, sen);
    printf("%s\n", to);
    return 0;
}

/**
Copies the characters from t into s, whereas viable
escape sequences are escaped and copied into s.
This assumes that s has enough memory to hold the
escaped sequences from t, plus, the original characters
from t.
*/
void escape(char s[], char t[]) {
    int c, si = 0, ti = 0;

    while ((c = t[ti++]) != '\0') {
        switch(c) {
        case '\t':
            s[si++] = '\\';
            s[si++] = 't';
            break;
        case '\n':
            s[si++] = '\\';
            s[si++] = 'n';
            break;
        default:
            s[si++] = c;
        }
    }
    s[si] = '\0';
}

/**
Copies the characters from to into s, whereas concurrent
characters, that would create an escape sequence (\n, \t)
are converting into an actual escape sequence character.
this results in the copied string potentially being smaller
than the original copied string t.
*/
void descape(char s[], char t[]) {
    int c, si = 0, ti = 0;

    while ((c = t[ti++]) != '\0') {
        switch (c) {
        case '\\':
            switch (t[ti]) {
            case 'n':
                s[si++] = 'n';
            case 't':
                s[si++] = 't';
            }
            break;
        default:
            s[si++] = c;
        }
    }
    s[si] = '\0';
}

void print(char arr[]) {
    int c, i = 0;
    while ((c = arr[i++]) != '\0')
        printf("%c", c);
    printf("\n");
}
