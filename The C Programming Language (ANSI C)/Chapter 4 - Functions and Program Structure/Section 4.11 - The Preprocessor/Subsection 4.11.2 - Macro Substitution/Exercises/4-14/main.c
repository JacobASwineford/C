#include <stdio.h>

#define swap(t, x, y) \
    t tem = x;        \
    x = y;            \
    y = tem;          \

/**
Define a macro swap(t, x, y) that interchanges two arguments
of type t. (Block structure will help.)
*/

void print(int[], int);

int main() {
    int arr[3] = {1, 2, 3};
    print(arr, 3);
    swap(int, arr[0], arr[2]);
    print(arr, 3);
    return 0;
}

void print(int arr[], int len) {
    putchar('[');
    int i;
    for (i = 0; i < len; i++) {
        if (i == len - 1)
            printf("%d", arr[i]);
        else
            printf("%d, ", arr[i]);
    }
    printf("]\n");
}
