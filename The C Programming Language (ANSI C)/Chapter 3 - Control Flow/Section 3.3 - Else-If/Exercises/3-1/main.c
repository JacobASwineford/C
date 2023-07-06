#include <stdio.h>

int binsearch(int, int[], int);
int binsearch2(int, int[], int);

/**
Our Binary search makes two tests inside the loop, when one
would suffice (at the price of more tests outside). Write a version
with only one test inside the loop and measure the difference in runtime.
*/

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int b = binsearch(5, arr, 5);
    int b2 = binsearch(5, arr, 5);
    printf("%d, %d\n", b, b2);
    return 0;
}

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n - 1] */
int binsearch(int x, int v[], int n) {
    int low, mid, high;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else /* found match  */
            return mid;
    }
    return -1; /* no match */
}

/**
Binsearch, except there is one test inside the loop instead of two.
*/
int binsearch2(int x, int v[], int n) {
    int low, mid, high;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = low + high / 2;
        if (x <= v[mid]) // <--- ONE TEST, EXCLUDING ELSE
            high = mid - 1;
        else
            low = mid + 1;
    }

    if (x == v[mid])
        return mid;

    return -1;
}
