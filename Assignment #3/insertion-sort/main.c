#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// https://pt.wikipedia.org/wiki/Insertion_sort#C
void insertion_sort(int arr[], int n) {
    int key, j;
    for (int i = 1;i < n;++i) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
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

    insertion_sort(arr, SIZE);

    printf("\n\n");

    for (int i = 0;i < SIZE;++i) {
        printf("arr[%d]: %d\n", i, arr[i]);
    }

    return 0;
}