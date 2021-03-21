#include "../linked-list/linked-list_ds.h"
#include <stdio.h>

typedef struct {
    struct slList* s;
    int size;
}sllStack;

// Cria a pilha vazia
sllStack* create_stack(void) {
    sllStack* stack = (sllStack*) malloc(sizeof(sllStack));

    if (stack) {
        stack->s = (struct slList*) malloc(sizeof(struct slList));
        stack->size = 0;
        return stack;
    } else {
        printf("Não há memória suficiente!\n");
        exit(1);
    }
}

// Adiciona elementos na pilha
void stack_push(sllStack* stack, float val) {
    sll_prepend(stack->s, val);
    stack->size++;
}

// Remove elementos da pilha
float stack_pop(sllStack* stack) {
    struct sllNode* node = stack->s->head;
    float v = node->val;
    stack->s->head = node->next;
    free(node);
    stack->size--;
    return v;
}

// Retorna o tamanho da pilha
int stack_size(sllStack* stack) {
    return stack->size;
}

// Verifica se a pilha está vazia
int stack_is_empty(sllStack* stack) {
    return (stack->s->head == NULL);
}

// Libera a memória alocada
void stack_clear(sllStack* stack) {
    struct sllNode* node = stack->s->head;
    while (node != NULL) {
        struct sllNode* aux = node->next;
        free(node);
        node = aux;
    }
    free(stack);
}
