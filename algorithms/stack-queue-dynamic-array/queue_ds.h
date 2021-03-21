#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float* queue;
    int size;
    int tail;
}Queue;

// Cria a fila
Queue* create_queue(void) {
    // Tenta alocar o espaço de memória necessário para struct Queue
    Queue* q = (Queue*) malloc(sizeof(Queue));

    if (q) {
        q->tail = -1; // Fila vazia
        q->size = 0;
        q->queue = (float*) malloc(q->size * sizeof(float));
    } else {
        printf("Não há memória suficiente!\n");
        exit(1);
    }

    return q;
}

// Verifica se a fila está vazia
int queue_is_empty(Queue* q) {
    if (!q) {
        // Caso a fila não exista, retorna -1
        return -1;
    }
    // Caso a fila exita, verifica se a mesma está vazia
    return (q->tail == -1);
}

// Retorna o tamanho da fila
int queue_size(Queue* q) {
    if (q) {
        // Retorna o tamanho da fila
        return (q->tail+1);
    }
    // Retorna -1 caso a fila não exista
    return -1;
}

// Insere elementos na fila
int queue_push(Queue* q, float val) {
    if (!q) {
        return -1;
    }

    if (q->tail == q->size-1) {
        int new_size = q->size == 0 ? 1 : q->size + 1;
        float* new_queue = (float*) realloc(q->queue, new_size);

        if (new_queue == NULL) {
            printf("Não há memória suficiente!\n");
            exit(1);
        }

        q->queue = new_queue;
        q->size = new_size;
    }

    if (q->tail < (q->size-1)) {
        q->tail++;
        q->queue[q->tail] = val;
        return 1;
    }

    return 0;
}

// Remove elementos da fila
float queue_pop(Queue* q) {
    if (!q) {
        return -1;
    }

    if (queue_is_empty(q)) {
        return -1;
    }

    // Valor do pop
    float aux = q->queue[0];

    // Realoca os elementos dentro do vetor para remover a posiçao 0
    for(int i = 0;i < q->tail; i++) {
        q->queue[i] = q->queue[i+1];
    }
    q->tail--;

    // Realoca o espaço de memória para de fato remover o elemento da fila
    float* new_queue = (float*) realloc(q->queue, (q->size-1));
    q->queue = new_queue;
    q->size--;

    return aux;
}

// Libera a memória alocada
void queue_clear(Queue* q) {
    free(q->queue);
    free(q);
}
