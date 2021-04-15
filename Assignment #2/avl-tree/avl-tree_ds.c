#include <stdio.h>
#include <stdlib.h>
#include "avl-tree_ds.h"

// Struct para armazenar os nós da árvore
struct node {
    int value;
    int height;
    struct node* left;
    struct node* right;
};

// Função para criar uma Árvore AVL
avlTree* avlTree_create(){
    avlTree* root = (avlTree*) malloc(sizeof(avlTree));
    if(root != NULL) {
        *root = NULL;
    }
    return root;
}

// Função para liberar cada nó
void avlTreeNode_clear(struct node* node){
    if(node == NULL) {
      return;
    }
    avlTreeNode_clear(node->left);
    avlTreeNode_clear(node->right);
    free(node);
    node = NULL;
}

// Função para liberar a árvore
void avlTree_clear(avlTree* root){
    if(root == NULL) {
      return;
    }
    avlTreeNode_clear(*root);
    free(root);
}

// Calcula a altura de um nó
int avlTreeNode_height(struct node* node) {
  if (node == NULL) {
    return -1;
  } else {
    return node->height;
  }
}

// Calcula o fator de balanceamento de um nó
int avlTreeNode_balance_factor(struct node* node) {
  return labs(avlTreeNode_height(node->left) - avlTreeNode_height(node->right));
}

// Calcula o maior valor
int bigger(int x, int y) {
  if (x > y) {
    return x;
  } else {
    return y;
  }
}

// Verifica se a árvore está vazia
int avlTree_empty(avlTree* root) {
  if (root == NULL) {
    return 1;
  }
  if (*root == NULL) {
    return 1;
  }
  return 0;
}

// Calcula a altura da árvore
int avlTree_height(avlTree* root) {
  if (root == NULL) {
    return 0;
  }
  if (*root == NULL) {
    return 0;
  }
  int left_height = avlTree_height(&((*root)->left));
  int right_height = avlTree_height(&((*root)->right));
  if (left_height > right_height) {
    return (left_height + 1);
  } else {
    return (right_height + 1);
  }
}

// Pré ordem
void avlTree_preorder(avlTree* root) {
  if (root == NULL) {
    return;
  }
  if (*root != NULL) {
    printf("Node: %d - Height: %d - Balance Factor: %d\n", (*root)->value, avlTreeNode_height(*root), avlTreeNode_balance_factor(*root));
    avlTree_preorder(&((*root)->left));
    avlTree_preorder(&((*root)->right));
  }
}

// Em order
void avlTree_inorder(avlTree* root) {
  if (root == NULL) {
    return;
  }
  if (*root != NULL) {
    avlTree_inorder(&((*root)->left));
    printf("Node: %d - Height: %d - Balance Factor: %d\n", (*root)->value, avlTreeNode_height(*root), avlTreeNode_balance_factor(*root));
    avlTree_inorder(&((*root)->right));
  }
}

// Pós ordem
void avlTree_postorder(avlTree* root) {
  if (root == NULL) {
    return;
  }
  if (*root != NULL) {
    avlTree_postorder(&((*root)->left));
    avlTree_postorder(&((*root)->right));
    printf("Node: %d - Height: %d - Balance Factor: %d\n", (*root)->value, avlTreeNode_height(*root), avlTreeNode_balance_factor(*root));
  }
}

// Busca na árvore
int avlTree_find_element(avlTree* root, int value) {
  if (root == NULL) {
    return 0;
  }
  struct node* current_node = *root;
  while (current_node != NULL) {
      if (value == current_node->value) {
        return 1;
      }
      if (value > current_node->value) {
        current_node = current_node->right;
      } else {
        current_node = current_node->left;
      }
  }
  return 0;
}

/*
Considerando que o nó C foi inserido como
filho do nó B, e que B é filho do nó A

Fator de balanceamento          Rotação
A = +2    e   B = +1            LL
A = -2    e   B = -1            RR
A = +2    e   B = -1            LR
A = -2    e   B = +1            RL

Rotações: https://pt.wikipedia.org/wiki/%C3%81rvore_AVL#Rota%C3%A7%C3%A3o
*/
void avlTree_rotationLL(avlTree* A) {
  // Simples a direita
  printf("RotationLL\n");
  struct node* B;
  B = (*A)->left;
  (*A)->left = B->right;
  B->right = *A;
  (*A)->height = bigger(avlTreeNode_height((*A)->left), avlTreeNode_height((*A)->right)) + 1;
  B->height = bigger(avlTreeNode_height(B->left), (*A)->height) + 1;
  *A = B;
}

void avlTree_rotationRR(avlTree* A) {
  // Simples a esquerda
  printf("RotationRR\n");
  struct node* B;
  B = (*A)->right;
  (*A)->right = B->left;
  B->left = (*A);
  (*A)->height = bigger(avlTreeNode_height((*A)->left), avlTreeNode_height((*A)->right)) + 1;
  B->height = bigger(avlTreeNode_height(B->right), (*A)->height) + 1;
  *A = B;
}

void avlTree_rotationLR(avlTree* A) {
  // Dupla a direita
  avlTree_rotationRR(&(*A)->left);
  avlTree_rotationLL(A);
}

void avlTree_rotationRL(avlTree* A) {
  // Dupla a esquerda
  avlTree_rotationLL(&(*A)->right);
  avlTree_rotationRR(A);
}

// Insere um elemento na árvore avl
/*
1. Root == NULL -> Insere o nó
2. Value < Root -> Vai para sub-árvore esquerda
3. Value > Root -> Vai para sub-árvore direita
4. Aplica recursão
5. Calcula as alturas de cada sub-árvore
6. Rotaciona se balance_factor for +2 ou -2
*/
int avlTree_insert(avlTree* root, int value) {
  int result;
  // Árvore vazia ou nó folha
  if (*root == NULL) {
    struct node* new_node;
    new_node = (struct node*) malloc(sizeof(struct node));
    if (new_node == NULL) {
      return 0;
    }
    new_node->value = value;
    new_node->height = 0;
    new_node->left = NULL;
    new_node->right = NULL;
    *root = new_node;
    return 1;
  }

  struct node* current_node = *root;
  // Insere à esquerda
  if (value < current_node->value) {
    // Se result == 1 o nó foi inserido, logo, precisamos verificar se é preciso
    // balancear a árvore
    if ((result = avlTree_insert(&(current_node->left), value)) == 1) {
      // Verifica se precisa balancear
      if (avlTreeNode_balance_factor(current_node) >= 2) {
        /*
        Se o valor inserido é menor que o valor
        do filho da esquerda da raiz, então a inserção foi
                  A
                 /
                B
               /
              C
        C é o nó inserido, precisamos fazer uma rotação simples a direita
        */ 
        if (value < (*root)->left->value) {
          avlTree_rotationLL(root);
        } else {
          /*
          Se o valor inserido não é menor que o valor do filho da esquerda
          da raiz, então a inserção foi
                    A
                   /
                  B
                   \
                    C
          Neste caso, precisamos fazer uma rotação dupla a direta
          */
          avlTree_rotationLR(root);
        }
      }
    }
  } else {
    // Insere à direita
    if (value > current_node->value) {
      // Se result == 1 o nó foi inserido, logo, precisamos verificar se é preciso
      // balancear a árvore
      if ((result = avlTree_insert(&(current_node->right), value)) == 1) {
        if (avlTreeNode_balance_factor(current_node) >= 2) {
          /*
          Se o valor inserido é menor que o valor
          do filho da esquerda da raiz, então a inserção foi
                    A
                     \
                      B
                       \
                        C
          C é o nó inserido, precisamos fazer uma rotação simples a esquerda
          */ 
          if ((*root)->right->value < value) {
            avlTree_rotationRR(root);
          } else {
            /*
            Se o valor inserido não é menor que o valor do filho da esquerda
            da raiz, então a inserção foi
                    A
                     \
                      B
                     /
                    C
            Neste caso, precisamos fazer uma rotação dupla a esquerda
            */
            avlTree_rotationRL(root);
          }
        }
      }
    } else {
      // Valor já está na ávore
      return 0;
    }
  }
  // Recalcula a altura do nó atual
  current_node->height = bigger(avlTreeNode_height(current_node->left), avlTreeNode_height(current_node->right)) + 1;
  return result;
}

// Procura o menor nó
struct node* find_smaller(struct node* current_node) {
  struct node* aux_1 = current_node;
  struct node* aux_2 = current_node->left;
  while (aux_2 != NULL) {
    aux_1 = aux_2;
    aux_2 = aux_2->left;
  }
  return aux_1;
}

// Remove um elemento da árvore avl
/*
1. Nó folha
2. Nó com 1 filho
3. Nó com 2 filhos
4. Balanceamento
Dica: Remover da sub-árvore da direita equivale a inserir um 
  nó na sub-árvore da esquerda
*/
int avlTree_remove(avlTree* root, int value) {
  // Valor não existe
  if (*root == NULL) {
    return 0;
  }
  int result;

  // Remove a esquerda
  if (value < (*root)->value) {
    // Se result == 1, removeu um nó
    if ((result = avlTree_remove(&(*root)->left, value)) == 1) {
      // Verifica se precisa balancear
      if (avlTreeNode_balance_factor(*root) >= 2) {
        /*
        Removemos um nó na subárvore da esquerda,
        então, precisamos verificar se é necessário
        balancear a subárvore da direita.
        */
        if (avlTreeNode_height((*root)->right->left) <= avlTreeNode_height((*root)->right->right)) {
          // Rotacão simples a esquerda
          avlTree_rotationRR(root);
        } else {
          // Rotação dupla a esquerda
          avlTree_rotationRL(root);
        }
      }
    }
  }

  // Remove a direita
  if (value > (*root)->value) {
    // Se result == 1, removeu um nó
    if ((result = avlTree_remove(&(*root)->right, value)) == 1) {
      // Verifica se precisa balancear
      if (avlTreeNode_balance_factor(*root) >= 2) {
        /*
        Removemos um nó na subárvore da direita,
        então, precisamos verificar se é necessário
        balancear a subárvore da esquerda.
        */
        if (avlTreeNode_height((*root)->left->right) <= avlTreeNode_height((*root)->left->left)) {
          // Rotação simples a direita
          avlTree_rotationLL(root);
        } else {
          // Rotação dupla a esquerda
          avlTree_rotationLR(root);
        }
      }
    }
  }

  // Remove a raiz
  if (value == (*root)->value) {
    // Nó tem 1 ou nenhum filho
    if (((*root)->left == NULL || (*root)->right == NULL)) {
      struct node* old_node = (*root);
      // Nó tem filho à esquerda
      if ((*root)->left != NULL) {
        *root = (*root)->left;
      } else {
        // Nó tem filho à direita
        *root = (*root)->right;
      }
      free(old_node);
    } else {
      // Nó tem 2 filhos
      // Procura o menor na sub-árvore da direita
      struct node* tmp = find_smaller((*root)->right);
      (*root)->value = tmp->value;

      // Remove o nó
      avlTree_remove(&(*root)->right, (*root)->value);
      
      // Verifica se precisa balancear
      if (avlTreeNode_balance_factor(*root) >= 2) {
        if (avlTreeNode_height((*root)->left->right) <= avlTreeNode_height((*root)->left->left)) {
          // Rotação simples a direita
          avlTree_rotationLL(root);
        } else {
          // Rotação dupla a direita
          avlTree_rotationLR(root);
        }
      }
    }

    if (*root) {
      // Recalcula a altura do nó atual
      (*root)->height = bigger(avlTreeNode_height((*root)->left), avlTreeNode_height((*root)->right)) + 1;
    }
    return 1;
  }

  // Recalcula a altura do nó atual
  (*root)->height = bigger(avlTreeNode_height((*root)->left), avlTreeNode_height((*root)->right)) + 1;
  return result;
}