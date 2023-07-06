#include <stdio.h>

void strncpy(char*, char*, int);
void strncat(char*, char*, int);
int strncmp(char*, char*, int);

/**
Write versions of the library functions strncpy, strncat,
and strncmp, which operate on at most the first n characters
of their strings. For example, strncpy(s, t, n) copies at most
n characters of t to s. Full descriptions are in Appendix B.
*/

int main() {
    char arr[100] = "Hello there!      ";
    char arr2[100] = "Hello Therez!";
    int i = strncmp(arr, arr2, 6);
    printf("'%s' %d\n", arr, i);
    return 0;
}
/**
copies at most n characters from t into s.
*/
void strncpy(char *s, char *t, int n) {
    while ((*s++ = *t++) && n--);
}

/**
Concatenates n characters from t onto the end of s.
*/
void strncat(char *s, char *t, int n) {
    while (*s) s++;
    while ((*s++ = *t++) && n-- != 0);
}

/**
compares the first n characters from s and t for
equality. if not equal, the lexical value of the
opposing characters is returned. (s - t)
*/
int strncmp(char *s, char *t, int n) {
    while ((*s == *t) && n-- != 0) {
        s++;
        t++;
    }

    if (n == 0)
        return 0;

    return *s - *t;
}
