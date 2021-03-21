#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar os dados das pessoas
typedef struct {
    long int CPF;
    char name[80];
}Person;

// Estrutura da hash table
typedef struct {
    int n; // Número de elementos armazenados
    int size; // Dimensão da tabela
    Person** p;
}Hash;

// Asinatura definida aqui para evitar warnings
void hsh_resize(Hash*);

// Função de hash
// h(k) = k mod N - Método de hash (Método da divisão)
int hash(Hash* table, long int CPF) {
    return (CPF % table->size);
}

// Segunda função de hash
// h(x) = (N - 2) - x mod (N - 2)
// N = Dimensão da hash table
// x = Chave = CPF
int hash2(Hash* table, long int CPF) {
    return (table->size - 2 - CPF % (table->size - 2));
}

// Função para criar a hash table
Hash* hsh_create(void) {
    // Aloca o espaço necessáro para a struct Hash
    Hash* table = (Hash*) malloc(sizeof(Hash));

    if (table) {
        table->n = 0;
        table->size = 7; // Dimensão inicial
        table->p = (Person**) malloc(table->size * sizeof(Person*));
        for (int i = 0;i < table->size;i++) {
            // Define como NULL toda a hash table
            table->p[i] = NULL;
        }
        return table;
    } else {
        printf("Não há memória suficiente disponível!\n");
        exit(1);
    }
}

// Função de busca na hash table
Person* hsh_find(Hash* table, long int CPF) {
    int h = hash(table, CPF); // Mapeamos a chave de busca com hash
    int h2 = hash2(table, CPF); // Mapeamos a chave de busca com hash2
    // Percorremos a hash table
    while (table->p[h] != NULL) {
        // Comparamos cada índice com o valor CPF
        if (table->p[h]->CPF == CPF) {
            return (table->p[h]);
        }
        h = (h+h2) % table->size; // Incremento circular
    }
    return NULL;
}

// Função para inserir elementos na hash table
Person* hsh_insert(Hash* table, Person* p) {
    // Verifica se a ocupação da hash table é maior que 75%
    if (table->n > 0.75 * table->size) {
        // Redimensiona a hash table
        hsh_resize(table);
    }
    
    int h = hash(table, p->CPF); // Mapeamos a chave de busca com hash
    int h2 = hash2(table, p->CPF); // Mapeamos a chave de busca com hash2
    
    // Verifica se a posição já está ocupada
    if (table->p[h] != NULL) {
        // Colisão, usaremos o double hashing
        for (int i = 1;i < table->size;i++) {
            int new_index = (h + h2 * i) % table->size; // Gera novo indíce
            if (table->p[new_index] == NULL) {
                h = new_index;
                break;
            }
        }
    }

    // Armazenamos a pessoa na hash table e incrementamos N
    table->p[h] = p;
    table->n++;

    // Retornamos a pessoa
    return p;
}

// Função para redimensionar a hash table quando o espaço
// utilizado for maior que 75%
void hsh_resize(Hash* table) {
    int old_size = table->size; // Tamanho antigo da hash table
    Person** prev = table->p; // Primeira pessoa (pointer)
    table->n = 0; // 0 o número de elementos armazenados
    table->size *= 1.947; // Fator fracionário para evitar múltiplos
    table->p = (Person**) malloc(table->size * sizeof(Person*)); // Realoca a hash table
    for (int i = 0;i < table->size;i++) {
        table->p[i] = NULL; // Define toda a hash table como NULL
    }
    for (int i = 0;i < old_size;i++) {
        // Insere elementos na tabela novamente
        hsh_insert(table, prev[i]);
    }
    // Libera a memória de prev
    free(prev);
}

// Função para printar a busca na hash table
void hsh_print(Hash* table, long int CPF) {
    Person* p = hsh_find(table, CPF);
    if (p) {
        printf("Nome: %s\n", p->name);
        printf("CPF: %ld\n\n", p->CPF);
    } else {
        printf("Pessoa não encontrada!\n\n");
    }
}

// Função para liberar a hash table
void hsh_clear(Hash* table) {
    for (int i = 0;i < table->size;i++) {
        // Algumas vezes table->p[i] == NULL
        // Isso não ocasionará erros
        free(table->p[i]);
    }
    free(table);
}
