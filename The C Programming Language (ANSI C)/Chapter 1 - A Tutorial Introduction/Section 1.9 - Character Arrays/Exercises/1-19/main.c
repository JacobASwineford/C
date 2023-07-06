#include <stdio.h>

/**
Write a function reverse(s) that reverses the character string s.
Use it to write a program that reverses it's input a line at a time.
*/

void reverse(char sen[], int len);

int main() {
    char buf[20] = "abcdefgh";
    reverse(buf, 8);
    printf("Reversed: %s\n", buf);

    return 0;
}

/**
Reverses the given string, in-place.
*/
void reverse(char sen[], int len) {
    int b = 0;
    int e = len - 1;
    char tmp;
    while (b < e) {
        tmp = sen[b];
        sen[b] = sen[e];
        sen[e] = tmp;
        b++;
        e--;
    }
}


