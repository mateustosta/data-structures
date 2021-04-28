/* 
Priority Queue - Extension of Queue
    Definition:
        1. All elements have a priority associated with them.
        2. A high priority element leaves the queue before a low priority element.
        3. If two (or more) elements have the same priority, then, they'll exit from
            the queue in the order that they appear in queue. (FIFO).

Binary Heap - A Binary Tree
    Definition:
        1. A binary heap is a complete tree. This property makes them suitable 
            to be stored in an array.
        2. There are two types of Binary Heap: MinHeap and MaxHeap. In MinHeap,
            the key at root (arr[0]) must be minimum among all keys present in
            Binary Heap. The same is valid recursively for all nodes in Binary Tree.
            In MaxHeap the key at root must be maximum among all keys present in
            Binary Heap, the same is valid recursively for all nodes in Binary Tree.
        3. The root element will always be at arr[0]. The parent of an arbitrary node
            will be at arr[(i-1)/2], where 'i' is the arbitrary node. The left child
            will be at arr[(2*i)+1] and the right child will be at arr[(2*i)+2]
    Example:
                    1
                   / \
                  3   6
                 / \ /
                5  9 8
    The array that represents this tree is:
    [1, 3, 6, 5, 9, 8]
    [root, left_child_of_root, right_child_of_root, left_child_of_left_child_of_root,...]

Operations defined here - Priority Queue using Heap - MaxHeap:
    1. heap_insert(priority) - Inserts a new element with priority 'priority'
    2. heap_extract_max() - Extracts an element with maximum priority.
    3. heap_remove(priority) - Removes an element pointed by 'priority'
    4. heap_get_max() - Returns an element with maximum priority.
    5. heap_change_priority(priority, new_priority) - Changes the priority of an element pointed
        by 'priority' to 'new_priority'.

References
https://www.geeksforgeeks.org/priority-queue-using-binary-heap/
https://en.wikipedia.org/wiki/Binary_heap
https://www.geeksforgeeks.org/priority-queue-set-1-introduction/
https://www.geeksforgeeks.org/binary-heap/
https://www.youtube.com/watch?v=cwi5U5jaBeI&list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka&index=85 - Portuguese reference
Books in README.md
*/

// ****** STRUCT ******
// This implementation uses an array with variable size, that starts in 10 (arbitrary)
typedef struct heap Heap;

struct heap {
    int size; // max size
    int n; // number of elements stored in heap (If 'n' reaches 75% of the size, 
           // the array will be increased by size*gold_number to get a better performance)
    int** arr; // pointer of pointer to data array
};

// ****** CORE ******
Heap* heap_create(void);
void heap_insert(Heap* heap, int* priority);
int heap_extract_max(Heap* heap);
void heap_remove(Heap* heap, int index);
int heap_get_max(Heap* heap);
void heap_change_priority(Heap* heap, int index, int new_priority);
void heap_print(Heap* heap);
int* heap_find(Heap* heap, int value);
void heap_clear(Heap* heap);
int heap_is_empty(Heap* heap);

// ****** AUXILIARY FUNCTIONS ******
void heap_resize(Heap* heap);
int heap_get_parent(int index);
int heap_get_left_child(int index);
int heap_get_right_child(int index);
void heap_shift_up(Heap* heap, int index);
void heap_shift_down(Heap* heap, int index); 
void heap_swap(Heap* heap, int index_1, int index_2);