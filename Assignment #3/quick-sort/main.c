#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int x = *a;
    *a = *b;
    *b = x;
}

int partition(int arr[], int start, int end) {
    int pivot = arr[end];
    int i = start-1;

    for (int j = start;j < end;++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i+1], &arr[end]);

    return i+1;
}

// https://github.com/mateustosta/icg/blob/main/problemas-javascript/3.js
void quick_sort(int arr[], int start, int end) {
    if (start >= end) {
        return;
    }

    int pivot = partition(arr, start, end);

    quick_sort(arr, start, pivot-1);
    quick_sort(arr, pivot+1, end);
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

    quick_sort(arr, 0, SIZE-1);

    printf("\n\n");

    for (int i = 0;i < SIZE;++i) {
        printf("arr[%d]: %d\n", i, arr[i]);
    }

    return 0;
}