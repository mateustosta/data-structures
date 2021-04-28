#include <stdio.h>
#include <stdlib.h>
#include "priority-queue_ds.h"

// Function to create a new heap
// Parameters: None
// Returns: Pointer to heap (if it has been created) / EXIT the program if
//      the heap (or the array arr) can't be created
Heap* heap_create(void) {
    // Attempts to allocate memory for the Heap
    Heap* heap = (Heap*) malloc(sizeof(Heap));

    // Checks whether memory allocation has been made
    if (heap) {
        heap->size = 10; // 10 is an arbitrary value
        heap->n = -1; // At first, the heap is empty. (-1 by default)
        // Attempts to allocate memory for the arr
        heap->arr = (int**) malloc(heap->size * sizeof(int*));
        // Checks whether memory allocation has been made
        if (heap->arr) {
            // Starts all arr's elements with NULL
            for (int i = 0;i < heap->size; ++i) {
                heap->arr[i] = NULL;
            }
        } else {
            printf("There is not enough memory available to allocate the arr array!\n");
            exit(1);
        }

        // Return the pointer to Heap
        return heap;
    } else {
        printf("There is not enough memory available to allocate the heap!\n");
        exit(1);
    }
}

// Function to insert a new element in the heap
// Parameters: Pointer to an existing heap and the priority of the new element
// Returns: None
void heap_insert(Heap* heap, int* priority) {
    // Checks if the Heap and the array arr exists
    if (!heap || !heap->arr) {
        return;
    }
    
    // if 'heap->n' equals to 75% of 'heap->size', 
    // then we will resize heap->arr
    if (heap->n > 0.75 * heap->size) {
        // resize heap->size
        // If there is any problem in resizing the heap, 
        // it will be dealt with in the heap_resize function.
        heap_resize(heap);
    }

    // Increases heap->n
    heap->n++;

    // Adds a new element on the heap.
    // We will always add this element at the 'n' position.
    heap->arr[heap->n] = priority;
    
    // Shift Up
    heap_shift_up(heap, heap->n);
}

// Function to extracts the element with maximum priority
// Parameters: Pointer to an existing heap
// Returns: Element with maximum priority
@TODO: Pensar em uma forma melhor de implementar essa função
int heap_extract_max(Heap* heap) {
    // Checks if the Heap and the array arr exists
    if (!heap || !heap->arr) {
        return -99999;
    }

    // Stores the root in result
    int result = *heap->arr[0];

    // Replace the value at the root with the last leaf
    *heap->arr[0] = *heap->arr[heap->n];
    heap->n--;

    // Shift Down the replaced element
    heap_shift_down(heap, 0);

    return result;
}

// Function to remove an element
// Parameters: Pointer to an existing heap and index of the element you want to remove
// Returns: None
void heap_remove(Heap* heap, int index) {
    // Checks if the Heap and the array arr exists
    if (!heap || !heap->arr) {
        return;
    }

    // Makes the element in the position pointed by "index" the largest element in the heap
    *heap->arr[index] = heap_get_max(heap) + 1;

    // Shift the node at the position pointed by "index" to the root
    heap_shift_up(heap, index);

    // Extract the node
    heap_extract_max(heap);
}

// Function to get value of the maximum element (root)
// Parameters: Pointer to an existing heap
// Returns: Value of the maximum element (root)
int heap_get_max(Heap* heap) {
    // Checks if the Heap and the array arr exists
    if (!heap || !heap->arr) {
        exit(1);
    }

    return *heap->arr[0];
}

// Function to change the priority of a node
// Parameters: Pointer to an existing heap, index of the node, and new priority
// Returns: None
void heap_change_priority(Heap* heap, int index, int new_priority) {
    // Checks if the Heap and the array arr exists
    if (!heap || !heap->arr) {
        return;
    }

    // Gets the element pointed by "index"
    int old_priority = *heap->arr[index];

    // Makes the priority of the element pointed by index being the new priority
    *heap->arr[index] = new_priority;

    // Shift Up if old_priority < new_priority
    if (old_priority < new_priority) {
        heap_shift_up(heap, index);
    } else {
        // Shift Down if old_priority > new_priority
        heap_shift_down(heap, index);
    }
}

// Function to print the heap
// Parameters: Pointer to an existing heap
// Returns: None
void heap_print(Heap* heap) {
    // Checks if the Heap and the array arr exists
    if (!heap || !heap->arr) {
        return;
    }

    for (int i = 0; i <= heap->n; ++i) {
        printf("INDEX: %d / VALUE: %d\n", i, *heap->arr[i]);
    }
    printf("\n");
}

// Function to find an element in heap
// Parameters: Pointer to an existing heap and the value to be searched
// Returns: Pointer to value (if found) / NULL (if not found)
int* heap_find(Heap* heap, int value) {
    // Checks if the Heap and the array arr exists
    if (!heap || !heap->arr) {
        exit(1);
    }

    for (int i = 0; i <= heap->n; ++i) {
        if (*heap->arr[i] == value) {
            return heap->arr[i];
        }
    }

    return NULL;
}

// Function to free memory
// Parameters: Pointer to an existing heap
// Returns: None
void heap_clear(Heap* heap) {
    // Checks if the Heap exists
    if (!heap || !heap->arr) {
        return;
    }

    for (int i = 0; i < heap->size; ++i) {
        free(heap->arr[i]);
    }

    free(heap->arr);
    free(heap);
}

// Function to check if the heap is empty
// Parameters: Pointer to an existing heap
// Returns: None
int heap_is_empty(Heap* heap) {
    // Checks if the Heap exists
    if (!heap) {
        exit(1);
    }

    return heap->n == -1;
}

// Function to resize the heap
// Parameters: Pointer to an existing heap
// Returns: None
void heap_resize(Heap* heap) {
    // Checks if the Heap and the array arr exists
    if (!heap || !heap->arr) {
        return;
    }
    
    int old_n = heap->n+1; // old n (number of elements in heap)
    int** prev = heap->arr; // pointer to the first element

    heap->n = -1;
    heap->size *= 1.61803399; // gold number
    // Attempts to allocate memory for the arr
    heap->arr = (int**) malloc(heap->size * sizeof(int*));
    // Checks whether memory allocation has been made
    if (heap->arr) {
        // Starts all arr's elements with NULL
        for (int i = 0;i < heap->size; ++i) {
            heap->arr[i] = NULL;
        }
    } else {
        printf("There is not enough memory available to allocate the arr array!\n");
        exit(1);
    }
    
    // Copy all the elements of "prev" into new heap
    for (int i = 0; i < old_n; ++i) {
        heap_insert(heap, prev[i]);
    }

    // Free the memory allocated to "prev"
    free(prev);
}

// Function to get the parent of a node
// Parameters: Pointer to an existing heap and index of the child node
// Returns: Index of parent
int heap_get_parent(int index) {
    // By definition, the parent of node "index" is at position ((index - 1) / 2)
    return (index - 1) / 2;
}

// Function to get the left child of the given node
// Parameters: Pointer to an existing heap and index of the node
// Returns: Index of left child
int heap_get_left_child(int index) {
    // By definition, the left child of node "index" is at position ((2*index) + 1)
    return (2*index) + 1;
}

// Function to get the right child of the given node
// Parameters: Pointer to an existing heap and index of the node
// Returns: Index of right child
int heap_get_right_child(int index) {
    // By definition, the right child of node "index" is at position ((2*index) + 2)
    return (2*index) + 2;
}

// Function to shift up the node
// Parameters: Pointer to an existing heap and index of the node
// Returns: None
void heap_shift_up(Heap* heap, int index) {
    // Checks if the Heap and the array arr exists
    if (!heap || !heap->arr) {
        return;
    }

    while (index > 0 && *heap->arr[heap_get_parent(index)] < *heap->arr[index]) {
        // Swap parent and current node
        heap_swap(heap, heap_get_parent(index), index);

        // Update "index" to parent of "index"
        index = heap_get_parent(index);
    }
}

// Function to shift down the node
// Parameters: Pointer to an existing heap and index of the node
// Returns: None
void heap_shift_down(Heap* heap, int index) {
    // Checks if the Heap and the array arr exists
    if (!heap || !heap->arr) {
        return;
    }

    int left_child = heap_get_left_child(index);

    while (left_child < heap->n) {
        int right_child = heap_get_right_child(index);

        if (right_child < heap->n && *heap->arr[right_child] > *heap->arr[left_child]) {
            left_child = right_child;
        }

        if (*heap->arr[left_child] < *heap->arr[index]) {
            break;
        }

        heap_swap(heap, index, left_child);

        index = left_child;

        left_child = heap_get_left_child(index);
    }
}

// Function to swap two elements
// Parameters: Pointer to an existing heap, index of the first node and, index of the second node
// Returns: None
void heap_swap(Heap* heap, int index_1, int index_2) {
    // Checks if the Heap and the array arr exists
    if (!heap || !heap->arr) {
        return;
    }

    int tmp = *heap->arr[index_1];
    *heap->arr[index_1] = *heap->arr[index_2];
    *heap->arr[index_2] = tmp;
}
