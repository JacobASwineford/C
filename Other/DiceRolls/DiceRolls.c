#include "../../testheaders.c"

/**
Runs a Monte Carlo Simulation to find out what dice number is rolled the most
with two dice.
*/
int main() {
    int OG_TEST_TIMES = 1000000;
    int TEST_TIMES = OG_TEST_TIMES;
    int could = 11;
    int r = 0;
    int r2 = 0;
    int arr[could];

    int i;
    for (i = 0; i < could; i++)
        arr[i] = 0;

    while (TEST_TIMES--) {
        r = (rand() % 6) + 1;
        r2 = (rand() % 6) + 1;
        arr[r + r2 - 2]++;
    }
    TEST_TIMES = OG_TEST_TIMES;

    int sum = 0;
    for (i = 0; i < could; i++) {
        printf("%-2d: %-10d: %.2f\%\n", i + 2, arr[i], ((double) arr[i] / TEST_TIMES) * 100);
        sum += arr[i];
    }

    printf("sum: %d\n", sum);

    return 0;
}
