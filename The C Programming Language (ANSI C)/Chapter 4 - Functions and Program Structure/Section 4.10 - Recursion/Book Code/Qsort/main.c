#include <stdio.h>

void qsort(int[], int, int);
void print(int[], int);

int main() {
    int arr[5] = {5, 4, 3, 2, 1};
    print(arr, 5);
    qsort(arr, 0, 4);
    print(arr, 5);
    return 0;
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(int v[], int left, int right) {
    int i, last;
    void swap(int v[], int i, int j);

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j) {
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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
