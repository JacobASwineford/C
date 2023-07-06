#include <stdio.h>

void strcat(char[], char[]);

int main() {

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
