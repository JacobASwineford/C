#include <stdio.h>

int strlen(char*);

int main() {

}

/* strlen: return length of string */
int strlen(char *s) {
    char *p = s;

    while (*p != '\0')
        p++;
    return p - s;
}
