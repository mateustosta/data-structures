#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float* stack;
    int size, top; // top == -1, vazia
}Stack;

Stack* create_stack(void) {
    // Tenta alocar o espaço de memória necessário para a struct
    Stack* st = (Stack*) malloc(sizeof(Stack));
    if (st != NULL) {
        // Atribui -1 a st->top para indicar que a pilha está vazia
        st->top = -1;
        st->size = 0; // Começa a pilha com tamanho 0 para usar a alocação dinâmica
        st->stack = (float*) malloc(st->size * sizeof(float)); // Reserva o espaço de memória inicial (0)
    } else {
        printf("Não há memória suficiente!\n");
        exit(1);
    }
    return st;
}

int stack_is_empty(Stack* st) {
    if (st == NULL) {
        // Caso a pilha não exista, retorna -1
        return -1;
    }
    // Caso contrário, verifica se a pilha está vazia
    return (st->top == -1);
}

int stack_size(Stack* st) {
    if (st != NULL) {
        // Retorna o tamanho da pilha
        return (st->top+1);
    }
    // Retorna -1 caso a pilha não exista
    return -1;
}

int stack_push(Stack* st, float info) {
    // Verifica se a pilha existe
    if (st == NULL) {
        return 0;
    }
    if (st->top == st->size-1) {
        // Caso o tamanho seja 0, ele irá para 1, caso seja maior que 0, 1 espaço adicional será adicionado
        int newSize = st->size == 0 ? 1 : st->size + 1;
        // Realoca o espaço de memória para o novo tamanho
        float* newStack = (float*) realloc(st->stack, newSize);

        if (newStack == NULL) {
            printf("Não há memória suficiente!\n");
            exit(1);
        }

        st->stack = newStack;
        st->size = newSize;
    }

    // Insere novos elementos na pilha
    if (st->top < (st->size-1)) {
        st->top++;
        st->stack[st->top] = info;
        return 1;
    }
}

float stack_pop(Stack* st) {
    // Verifica se a pilha existe
    if (st == NULL) {
        return -1;
    }

    // Verifica se a pilha está vazia
    if (st->top == -1) {
        return 0;
    }

    // Remove logicamente o elemento da pilha
    float temp = st->stack[st->top];
    st->top--;
    
    // Realoca o espaço de memória para de fato remover o elemento da pilha
    float* newStack = (float*) realloc(st->stack, (st->size-1));
    st->stack = newStack;
    st->size--;

    return temp;
}

void stack_clear(Stack* st) {
    // Libera a memória alocada no array e na struct
    free(st->stack);
    free(st);
}
