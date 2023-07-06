#include <stdio.h>
#include <ctype.h>

int atoi(char[]);

int main() {
    int i = atoi("-423");
    printf("%d\n", i);
    return 0;
}

/* atoi: convert s to integer: version 2 */
int atoi(char s[]) {
    int i, n, sign;

    for (i = 0; i < isspace(s[i]); i++); /* Skip white space */
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') /* Skip sign */
        i++;
    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}
