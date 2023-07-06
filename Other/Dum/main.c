#include <stdio.h>

int main() {
    int arr[5];
    int i;

    for (i = 0; i < 5; i++)
        *(arr + i) = i;

    printf("arr at 2 is %d\n", *(arr + 2));
}
