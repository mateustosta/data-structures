#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int x = *a;
    *a = *b;
    *b = x;
}

int selection(const int arr[], int n) {
    int i = 0;
    for (int j = 1;j < n;++j) {
        if (arr[i] < arr[j]) {
            i = j;
        }
    }
    return i;
}

void selection_sort(int arr[], int n) {
    while (n > 1) {
        int ind = selection(arr, n);
        swap(&arr[ind], &arr[n-1]);
        n--;
    }
}

int main(void) {
    int SIZE = 50;
    int* arr = (int*) malloc(SIZE * sizeof(int));

    srand(time(0));

    for (int i = 0;i < SIZE;++i) {
        // rand() % (max_number + 1 - minimum_number) + minimum_number
        // https://stackoverflow.com/questions/1202687/how-do-i-get-a-specific-range-of-numbers-from-rand
        arr[i] = rand() % (500 + 1 - 0) + 0;
    }

    for (int i = 0;i < SIZE;++i) {
        printf("arr[%d]: %d\n", i, arr[i]);
    }

    selection_sort(arr, SIZE);

    printf("\n\n");

    for (int i = 0;i < SIZE;++i) {
        printf("arr[%d]: %d\n", i, arr[i]);
    }

    return 0;
}