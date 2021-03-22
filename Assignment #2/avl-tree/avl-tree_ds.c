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
bTree* bTree_create(){
    bTree* root = (bTree*) malloc(sizeof(bTree));
    if(root != NULL) {
        *root = NULL;
    }
    return root;
}

// Função para liberar cada nó
void btNode_clear(struct node* node){
    if(node == NULL) {
      return;
    }
    btNode_clear(node->left);
    btNode_clear(node->right);
    free(node);
    node = NULL;
}

// Função para liberar a árvore
void bTree_clear(bTree* root){
    if(root == NULL) {
      return;
    }
    btNode_clear(*root);
    free(root);
}

// Calcula a altura de um nó
int btNode_height(struct node* node) {
  if (node == NULL) {
    return -1;
  } else {
    return node->height;
  }
}

// Calcula o fator de balanceamento de um nó
int btNode_balance_factor(struct node* node) {
  //printf("NODE: %d\nBALANCE_FACTOR: %d\n", node->value,labs(btNode_height(node->left) - btNode_height(node->right)));
  return labs(btNode_height(node->left) - btNode_height(node->right));
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
int bTree_empty(bTree* root) {
  if (root == NULL) {
    return 1;
  }
  if (*root == NULL) {
    return 1;
  }
  return 0;
}

// Calcula a altura da árvore
int bTree_height(bTree* root) {
  if (root == NULL) {
    return 0;
  }
  if (*root == NULL) {
    return 0;
  }
  int left_height = bTree_height(&((*root)->left));
  int right_height = bTree_height(&((*root)->right));
  if (left_height > right_height) {
    return (left_height + 1);
  } else {
    return (right_height + 1);
  }
}

// Pré ordem
void bTree_preorder(bTree* root) {
  if (root == NULL) {
    return;
  }
  if (*root != NULL) {
    printf("Node: %d - Height: %d - Balance Factor: %d\n", (*root)->value, btNode_height(*root), btNode_balance_factor(*root));
    bTree_preorder(&((*root)->left));
    bTree_preorder(&((*root)->right));
  }
}

// Em order
void bTree_inorder(bTree* root) {
  if (root == NULL) {
    return;
  }
  if (*root != NULL) {
    bTree_inorder(&((*root)->left));
    printf("Node: %d - Height: %d - Balance Factor: %d\n", (*root)->value, btNode_height(*root), btNode_balance_factor(*root));
    bTree_inorder(&((*root)->right));
  }
}

// Pós ordem
void bTree_postorder(bTree* root) {
  if (root == NULL) {
    return;
  }
  if (*root != NULL) {
    bTree_postorder(&((*root)->left));
    bTree_postorder(&((*root)->right));
    printf("Node: %d - Height: %d - Balance Factor: %d\n", (*root)->value, btNode_height(*root), btNode_balance_factor(*root));
  }
}

// Busca na árvore
int bTree_find_element(bTree* root, int value) {
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
*/
void bTree_rotationLL(bTree* A) {
  printf("RotationLL\n");
  struct node* B;
  B = (*A)->left;
  (*A)->left = B->right;
  B->right = *A;
  (*A)->height = bigger(btNode_height((*A)->left), btNode_height((*A)->right)) + 1;
  B->height = bigger(btNode_height(B->left), (*A)->height) + 1;
  *A = B;
}

void bTree_rotationRR(bTree* A) {
  printf("RotationRR\n");
  struct node* B;
  B = (*A)->right;
  (*A)->right = B->left;
  B->left = (*A);
  (*A)->height = bigger(btNode_height((*A)->left), btNode_height((*A)->right)) + 1;
  B->height = bigger(btNode_height(B->right), (*A)->height) + 1;
  *A = B;
}

void bTree_rotationLR(bTree* A) {
  bTree_rotationRR(&(*A)->left);
  bTree_rotationLL(A);
}

void bTree_rotationRL(bTree* A) {
  bTree_rotationLL(&(*A)->right);
  bTree_rotationRR(A);
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
int bTree_insert(bTree* root, int value) {
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
    if ((result = bTree_insert(&(current_node->left), value)) == 1) {
      // Verifica se precisa balancear
      if (btNode_balance_factor(current_node) >= 2) {
        if (value < (*root)->left->value) {
          bTree_rotationLL(root);
        } else {
          bTree_rotationLR(root);
        }
      }
    }
  } else {
    // Insere à direita
    if (value > current_node->value) {
      if ((result = bTree_insert(&(current_node->right), value)) == 1) {
        if (btNode_balance_factor(current_node) >= 2) {
          if ((*root)->right->value < value) {
            bTree_rotationRR(root);
          } else {
            bTree_rotationRL(root);
          }
        }
      }
    } else {
      // Valor já está na ávore
      return 0;
    }
  }
  // Recalcula a altura do nó atual
  current_node->height = bigger(btNode_height(current_node->left), btNode_height(current_node->right)) + 1;
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
  // nó na sub-árvore da esquerda
*/
int bTree_remove(bTree* root, int value) {
  // Valor não existe
  if (*root == NULL) {
    return 0;
  }
  int result;

  // Remove a esquerda
  if (value < (*root)->value) {
    if ((result = bTree_remove(&(*root)->left, value)) == 1) {
      // Verifica se precisa balancear
      if (btNode_balance_factor(*root) >= 2) {
        if (btNode_height((*root)->right->left) <= btNode_height((*root)->right->right)) {
          bTree_rotationRR(root);
        } else {
          bTree_rotationRL(root);
        }
      }
    }
  }

  // Remove a direita
  if (value > (*root)->value) {
    if ((result = bTree_remove(&(*root)->right, value)) == 1) {
      // Verifica se precisa balancear
      if (btNode_balance_factor(*root) >= 2) {
        if (btNode_height((*root)->left->right) <= btNode_height((*root)->left->left)) {
          bTree_rotationLL(root);
        } else {
          bTree_rotationLR(root);
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
      bTree_remove(&(*root)->right, (*root)->value);
      
      // Verifica se precisa balancear
      if (btNode_balance_factor(*root) >= 2) {
        if (btNode_height((*root)->left->right) <= btNode_height((*root)->left->left)) {
          bTree_rotationLL(root);
        } else {
          bTree_rotationLR(root);
        }
      }
    }

    if (*root) {
      // Recalcula a altura do nó atual
      (*root)->height = bigger(btNode_height((*root)->left), btNode_height((*root)->right)) + 1;
    }
    return 1;
  }

  // Recalcula a altura do nó atual
  (*root)->height = bigger(btNode_height((*root)->left), btNode_height((*root)->right)) + 1;
  return result;
}