#include <stdio.h>

/**
Write a program to print the corresponding Celsius to Fahrenheit
table.
*/

int main() {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    celsius = lower;
    printf("%s %s\n", "Celsius", "Fahrenheit");
    while (celsius <= upper) {
        fahr = (9.0 / 5.0) * celsius + 32.0;
        printf("%-7.0f %10.1f\n", celsius, fahr);
        celsius += step;
    }

    return 0;
}
