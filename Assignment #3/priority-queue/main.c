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

    Heap* heap = heap_create();

    Node* node1 = (Node*) malloc(sizeof(Node));
    node1->value = 45;
    heap_insert(heap, node1);

    Node* node2 = (Node*) malloc(sizeof(Node));
    node2->value = 20;
    heap_insert(heap, node2);

    Node* node3 = (Node*) malloc(sizeof(Node));
    node3->value = 14;
    heap_insert(heap, node3);

    Node* node4 = (Node*) malloc(sizeof(Node));
    node4->value = 12;
    heap_insert(heap, node4);

    Node* node5 = (Node*) malloc(sizeof(Node));
    node5->value = 31;
    heap_insert(heap, node5);
    
    Node* node6 = (Node*) malloc(sizeof(Node));
    node6->value = 7;
    heap_insert(heap, node6);

    Node* node7 = (Node*) malloc(sizeof(Node));
    node7->value = 11;
    heap_insert(heap, node7);

    Node* node8 = (Node*) malloc(sizeof(Node));
    node8->value = 45;
    heap_insert(heap, node8);

    Node* node9 = (Node*) malloc(sizeof(Node));
    node9->value = 7;
    heap_insert(heap, node9);

    heap_print(heap);

    printf("Max value: %d\n", heap_extract_max(heap));

    heap_print(heap);

    heap_change_priority(heap, 2, 49);

    heap_print(heap);

    heap_remove(heap, 3);

    heap_print(heap);

    heap_clear(heap);

    return 0;
}