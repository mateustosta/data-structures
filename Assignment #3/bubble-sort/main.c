#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int x = *a;
    *a = *b;
    *b = x;
}

void bubble_sort(int arr[], int n) {
    for (int i = 0;i <= n-1;++i) {
        for (int j = 0;j < n-1;++j) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
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

    bubble_sort(arr, SIZE);

    printf("\n\n");

    for (int i = 0;i < SIZE;++i) {
        printf("arr[%d]: %d\n", i, arr[i]);
    }

    return 0;
}