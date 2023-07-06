#include <stdio.h>
#include <string.h>

/**
Write a recursive version of the function reverse(s),
which reverses the string s in place.

The big problem with this is that the length of the string
needs to be known, to know what needs to be the endpoint for
reversal. This can be solved by having the caller
specify how many characters at the beginning of the
string are to be replaced.

OR, by constantly assigning b and e based on the current state
of the method. This is a bit weirder.
*/

void reverse(char[]);

int main() {
    char buf[100] = {'a', 'b', 'c', 'd', 'e'};
    reverse(buf);
    printf("%s\n", buf);
    return 0;
}

/**
Reverses the string in place.
*/
void reverse(char str[]) {
    static int b = 0;
    static int e = 0;
    static int es = 0;

    e = (strlen(str) - 1) - es++;

    if (b >= e)
        return;

    char temp = str[b];
    str[b++] = str[e];
    str[e--] = temp;

    printf("%s\n", str);
    reverse(str);
}

