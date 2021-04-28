#include <stdio.h>
#include <stdlib.h>
#include "priority-queue_ds.h"

int main(void) {
    /*
              45
           /      \
          31       14
         /  \      / \
        13   20   7  11
       /  \
      12   7 
    */

    // Create a heap. If a problem occurs (memory allocation, etc.) it will be handled by TAD.
    Heap* heap = heap_create();

    // Empty
    // 1 = Empty
    // 0 = Not empty
    printf("Empty: %d\n\n", heap_is_empty(heap));

    // Create the nodes
    int* node1 = (int*) malloc(sizeof(int));
    *node1 = 45;
    heap_insert(heap, node1);

    int* node2 = (int*) malloc(sizeof(int));
    *node2 = 20;
    heap_insert(heap, node2);

    int* node3 = (int*) malloc(sizeof(int));
    *node3 = 14;
    heap_insert(heap, node3);

    int* node4 = (int*) malloc(sizeof(int));
    *node4 = 12;
    heap_insert(heap, node4);

    int* node5 = (int*) malloc(sizeof(int));
    *node5 = 31;
    heap_insert(heap, node5);
    
    int* node6 = (int*) malloc(sizeof(int));
    *node6 = 7;
    heap_insert(heap, node6);

    int* node7 = (int*) malloc(sizeof(int));
    *node7 = 11;
    heap_insert(heap, node7);

    int* node8 = (int*) malloc(sizeof(int));
    *node8 = 13;
    heap_insert(heap, node8);

    int* node9 = (int*) malloc(sizeof(int));
    *node9 = 7;
    heap_insert(heap, node9);

    // Empty
    // 1 = Empty
    // 0 = Not empty
    printf("Empty: %d\n\n", heap_is_empty(heap));

    // Find
    // Returns a pointer to the node if it is found
    // Returns null if not found
    int* value = heap_find(heap, 20);
    if (value) {
        printf("Find: %d\n\n", *value);
    } else {
        printf("Value not found!\n\n");
    }

    // Prints the heap (in the order in which the elements appear in the array)
    heap_print(heap);

    // Print the max value of the heap and removes it from the heap
    printf("Max value: %d\n\n", heap_extract_max(heap));

    // Prints the heap (in the order in which the elements appear in the array)
    heap_print(heap);

    // Changes the element's priority in the index to the new given priority
    heap_change_priority(heap, 2, 49);

    // Prints the heap (in the order in which the elements appear in the array)
    heap_print(heap);

    // Removes the element in the given index
    heap_remove(heap, 3);

    // Prints the heap (in the order in which the elements appear in the array)
    heap_print(heap);

    // Frees the memory allocated to the heap
    heap_clear(heap);

    return 0;
}