#ifndef BINARY_TREE_DS_H
#define BINARY_TREE_DS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node btNode;
typedef struct tree bTree;

// Struct para armazenar os nós da árvore
struct node {
  int value;
  btNode* left;
  btNode* right;
};

// Struct para armazenar a raiz da árvore
struct tree {
  btNode* root;
};

// Função para criar a árvore
bTree* bTree_create(btNode* root) {
  bTree* tree = (bTree*) malloc(sizeof(bTree));
  if (tree) {
    tree->root = root;
    return tree;
  } else {
    printf("Ocorreu um erro na criação da árvore!\n");
    exit(0);
  }
}

// Função para criar os nós da árvore
btNode* bTree_create_node(int value, btNode* left, btNode* right) {
  btNode* node = (btNode*) malloc(sizeof(btNode));
  if (node) {
    node->value = value;
    node->left = left;
    node->right = right;
    return node;
  } else {
    printf("Ocorreu um erro na criação do nó!\n");
    exit(0);
  }
}

// Função para liberar a memória de cada nó da árvore
void btNode_clear(btNode* root) {
  if (root) {
    btNode_clear(root->left);
    btNode_clear(root->right);
    free(root);
  }
}

// Função para liberar a memória da estrutura da árvore
void bTree_clear(bTree* tree) {
  btNode_clear(tree->root);
  free(tree);
}

// Função para printar cada nó da árvore
void btNode_print(btNode* root) {
  printf("<");
  if (root) {
    printf("%d", root->value);
    btNode_print(root->left);
    btNode_print(root->right);
  }
  printf(">");
}

// Função para printar a árvore
void bTree_print(bTree* tree) {
  btNode_print(tree->root);
}

// Função para buscar um valor nó a nó
// Método = Pré-ordem (raiz, esquerda, direita)
btNode* btNode_find(btNode* root, int value) {
  if (!root) {
    return NULL;
  } else if (value == root->value) {
    return root;
  } else {
    btNode* node = btNode_find(root->left, value);
    if (node) {
      return node;
    } else {
      return btNode_find(root->right, value);
    }
  }
}

// Função para buscar um valor na árvore
btNode* bTree_find(bTree* tree, int value) {
  return btNode_find(tree->root, value);
}

#endif