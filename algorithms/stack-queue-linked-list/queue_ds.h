#include "../linked-list/linked-list_ds.h"
#include <stdio.h>

typedef struct {
    struct slList* q;
    int size;
}sllQueue;

// Cria a fila vazia
sllQueue* create_queue(void) {
    sllQueue* queue = (sllQueue*) malloc(sizeof(sllQueue));

    if (queue) {
        queue->q = (struct slList*) malloc(sizeof(struct slList));
        queue->q->head = NULL;
        return queue;
    } else {
        printf("Não há memória suficiente!\n");
        exit(1);
    }
}

// Adiciona elementos na fila
float queue_push(sllQueue* queue, float val) {
    sll_prepend(queue->q, val);
    queue->size++;
}

// Remove elementos da fila
float queue_pop(sllQueue* queue) {
    struct sllNode* aux = queue->q->head;
    struct sllNode* prev = NULL;

    // Caso em que só tem 1 elemento na fila
    if (queue->q->head->next == NULL) {
        float v = queue->q->head->val;
        queue->q->head = NULL;
        queue->size--;
        return v;
    }

    while (aux->next != NULL) {
        prev = aux;
        aux = aux->next;
    }

    if (queue->size > 0) {
        float v = aux->val;
        prev->next = NULL;
        free(aux);
        queue->size--;
        return v;
    }

    return 0;
}

// Retorna o tamanho da fila
int queue_size(sllQueue* queue) {
    return queue->size;
}

// Verifica se a fila está vazia
int queue_is_empty(sllQueue* queue) {
    return (queue->q->head == NULL);
}

// Libera a memória alocada
void queue_clear(sllQueue* queue) {
    struct sllNode* node = queue->q->head;
    while (node != NULL) {
        struct sllNode* aux = node->next;
        free(node);
        node = aux;
    }
    free(queue);
}
