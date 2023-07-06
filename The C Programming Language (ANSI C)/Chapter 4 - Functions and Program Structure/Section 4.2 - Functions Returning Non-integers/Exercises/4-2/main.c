#include <ctype.h>
#include <stdio.h>
#include <math.h>

#define MAXLINE 100

double atof(char[]);
double atof2(char[]);

/**
Extend atof to handle scientific notation of the form
123.45e-6
where a floating point number may be followed by e or E and
an optionally signed exponent.
*/

int main() {
    char line[MAXLINE] = "123.45e6";
    double d = atof2(line);
    printf("the number, from %s, is %f\n", line, d, d);

    return 0;
}

/* convert string s to double */
double atof(char s[])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++); /* skip white space */

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    return sign * val / power;
}

/**
Converts string s t double, with the additional functionality
of handling scientific notation in the form
123.45e-6 (sign is optional after e)
*/
double atof2(char s[]) {
    double val, power;
    int i, sign, esign, epower;

    for (i = 0; isspace(s[i]); i++); /* skip white space */

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    // extension
    if (s[i] != 'e' && s[i] != 'E')
        return sign * val / power;

    i++;
    esign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '-')
        i++;
    for (epower = 0; isdigit(s[i]); i++)
        epower = 10 * epower + (s[i] - '0');

    epower *= esign;
    return (sign * val / power) * pow(10, epower);

}

