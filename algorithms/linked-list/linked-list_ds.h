#include <stdio.h>
#include <stdlib.h>

struct slList {
    struct sllNode* head;
};

struct sllNode {
    float val;
    struct sllNode* next;
};

struct slList* create_list(void) {
    struct slList* list = (struct slList*) malloc(sizeof(struct slList));

    if (list) {
        list->head = NULL;
        return list;
    } else {
        printf("Não há memória suficiente!\n");
        exit(1);
    }
}

void sll_prepend(struct slList* list, float val) {
    struct sllNode* node = (struct sllNode*) malloc(sizeof(struct sllNode));

    if (node) {
        node->val = val;
        node->next = list->head;
        list->head = node; 
    } else {
        printf("Não há memória suficiente!\n");
        exit(1);
    }
}
