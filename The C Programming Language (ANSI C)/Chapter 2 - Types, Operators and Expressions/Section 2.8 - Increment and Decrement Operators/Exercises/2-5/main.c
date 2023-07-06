#include <stdio.h>

/**
Write the function any(s1,s2) which returns the first location in the
string s1 where any character from the string s2 occurs, or -1 if s1
contains no characters from s2. (The standard library function strpbrk does
the same job but returns a pointer to that location).
*/

int any(char[], char[]);
int in(char, char[]);

int main() {
    char hi[10] = "hi there";
    char name[11] = "i am jacob";
    int a = any(hi, name);
    printf("%d %c\n", a, hi[a]);
    return 0;
}

/**
Returns the first location of a character in s1 that is also contained
in s2. This method returns -1 if s1 contains no characters from s2.
*/
int any(char s1[], char s2[]) {
    char c;
    int ins, i = 0;
    while ((c = s1[i]) != '\0') {
        if (in(c, s2))
            return i;
        i++;
    }
    return -1;
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
