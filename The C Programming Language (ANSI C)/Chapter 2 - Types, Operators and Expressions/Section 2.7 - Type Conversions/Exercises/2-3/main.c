#include <stdio.h>
#include <math.h>
#include <string.h>

/**
Write a function htoi(s), which converts a string of
hexadecimal digits (including an optional 0x or 0X) into its
equivalent integer value.
*/

int htoi(char[]);

int main() {
    char hex[5] = "\\x17";
    int val = htoi(hex);
    printf("the value of %s is %d\n", hex, val);
    return 0;
}

/**
Converts a string of hexadecimal digits into it's corresponding
integer value. This method expects arguments in the form of
"\\x..."
*/
int htoi(char s[]) {
    int i = 0, n = 0, len = strlen(s) - 1;
    char c;
    int b;

    while ((c = s[len]) != 'x')
        n += (s[len--] - '0') * pow(16, i++);

    return n;
}

