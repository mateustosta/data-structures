#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void heapify(int arr[], int size, int i) {
	int max = i;
	int left_child = (2*i) + 1;
	int right_child = (2*i) + 2;

	if (left_child < size && arr[left_child] > arr[max]) {
		max = left_child;
	}

	if (right_child < size && arr[right_child] > arr[max]) {
		max = right_child;
	}

	if (max != i) {
		swap(&arr[i], &arr[max]);
		heapify(arr, size, max);
	}
}

void heap_sort(int arr[], int size) {
	for (int i = (size/2)-1;i >= 0;--i) {
		heapify(arr, size, i);
	}

	for (int i = size-1;i >= 0;--i) {
		swap(&arr[0], &arr[i]);
		heapify(arr, i, 0);
	}
}

int main() {
	int SIZE = 10;
	int* arr = (int*) malloc(SIZE * sizeof(int));

	srand(time(0));

	for (int i = 0;i < SIZE;++i) {
		// rand() % (max + 1 - min) + min
		arr[i] =  rand() % (500 + 1 - 0) + 0;
	}

	for (int i = 0;i < SIZE;++i) {
		printf("arr[%d]: %d\n", i, arr[i]);
	}

	heap_sort(arr, SIZE);

	printf("\n\n");

	for (int i = 0;i < SIZE;++i) {
		printf("arr[%d]: %d\n", i, arr[i]);
	}

	return 0;
}
