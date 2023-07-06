#include <stdio.h>

int atoi(char[]);

int main() {
    char str[6] = "12345";
    int con = atoi(str);
    printf("the value of %s is: %d\n", str, con);
    return 0;
}

/* atoi: convert s to integer */
int atoi(char s[]) {
    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}
