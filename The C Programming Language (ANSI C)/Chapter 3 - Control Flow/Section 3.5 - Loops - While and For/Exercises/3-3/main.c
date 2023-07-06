#include <stdio.h>

/**
Write a function expand(s1,s2) that expands shorthand notation
like a-z in the string s1 into the equivalent complete list abc...xyz
in s2. Allow for letters of either case or digits, and be prepared to handle
cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is
taken literally.

I'm not too entirely sure what it means that a leading or trailing - is taken
"literally", since there is either no defined endpoint or beginning point.
So, I'm treating this as an error.
*/

void expand(char[], char[]);
int generate(char, char, int, char[]);

int main() {
    char arr[1000];
    expand("1-9-c", arr);
    printf("sentence: %s\n", arr);
    return 0;
}

/**
Expands shorthand notation for a list, such as a-z,
into a literal list with all elements within that range.
there may be multiple ranges defined, in which case the
complete lists will be expanded from left to right,
and continued to be appended to previous lists.

This covers ASCII only (characters 0 - 255).
*/
void expand(char s1[], char s2[]) {
    int s1i = 0;
    int s2i = 0;
    int con = 0;
    int t;
    char c, begin = 0, end = 0;
    while ((c = s1[s1i++]) != '\0') {
            printf("%c\n", c);
        switch (c) {
        case '-':
            if (begin)
                con = 1;
                break;
        default:
            if (!begin)
                begin = c;
            else if (con && !end) {
                end = c;
                s2i += generate(begin, end, s2i, s2);
                begin = end;
                end = 0;
                con = 0;
            }
        }
    }
    s2[s2i] = '\0';
}

/**
Generates and writes into "into" a list from the ASCII
table from the starting point to an end point. This method assumes that
there is enough space for a list to be stored in "into", and from <= to.
Any input not compliant with these rules will result in undefined behavior.

This covers ACSII only (characters 0 - 255)
*/
int generate(char from, char to, int index, char into[]) {
    printf("generate from: %c, to: %c, index: %d\n", from, to, index);
    int c = from;
    int len = 0;
    while (c < to + 1) {
        into[index++] = c;
        c++;
        len++;
    }
    return len;
}
