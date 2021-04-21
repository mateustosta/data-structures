#include <stdio.h>
#include <stdlib.h>
#include "binary-search-tree_ds.h"

// Função para criar a árvore
bsTree* bsTree_create(void) {
	bsTree* tree = (bsTree*) malloc(sizeof(bsTree));
	if (tree) {
		tree->root = NULL;
		return tree;
	} else {
		printf("Ocorreu um erro!\n");
		exit(0);
	}
}

// Função para inserir valores nos nós da árvore
bstNode* bstNode_insert(bstNode* root, int value) {
	// valor já está na árvore
    if (bstNode_find(root, value)) {
        return NULL;
    }
	if (!root) {
		root = (bstNode*) malloc(sizeof(bstNode));
		root->value = value;
		root->left = NULL;
		root->right = NULL;
	} else if (value < root->value) {
		// O valor é menor que a raiz, vamos para a esquerda
		root->left = bstNode_insert(root->left, value);
	} else {
		// O valor é maior que a raiz, vamos para a direta
		root->right = bstNode_insert(root->right, value);
	}
	return root;
}

// Função para inserir valores na árvore
void bsTree_insert(bsTree* tree, int value) {
	tree->root = bstNode_insert(tree->root, value);
}

// Função para prucurar o nó a ser removido
bstNode* bstNode_remove(bstNode* root, int value) {
	if (!root) {
		return NULL;
	} else if (root->value > value) {
		// Root > Value = esquerda
		root->left = bstNode_remove(root->left, value);
	} else if (root->value < value) {
		// Root < Value = direita
		root->right = bstNode_remove(root->right, value);
	} else {
		// Achou o elemento
		if (root->left == NULL && root->right == NULL) {
			// Elemento não tem filhos
			free(root);
			root = NULL;
		} else if (root->left == NULL) {
			// Elemento tem filho(s) à direita
			bstNode* temporary_node = root;
			root = root->right;
			free(temporary_node);
		} else if (root->right == NULL) {
			// Elemento tem filho(s) à esquerda
			bstNode* temporary_node = root;
			root = root->left;
			free(temporary_node);
		} else {
			// Elemento tem filho(s) à direita e à esquerda
			bstNode* aux = root->left;
			while (aux->right) {
				aux = aux->right;
			}
			root->value = aux->value;
			aux->value = value;
			root->left = bstNode_remove(root->left, value);
		}
	}
	return root;
}

// Função para remover valores da árvore
void bsTree_remove(bsTree* tree, int value) {
	tree->root = bstNode_remove(tree->root, value);
}

// Função para liberar a memória de cada nó da árvore
void bstNode_clear(bstNode* root) {
	if (root) {
		bstNode_clear(root->left);
		bstNode_clear(root->right);
		free(root);
	}
}

// Função para liberar a memória da estrutura da árvore
void bsTree_clear(bsTree* tree) {
	bstNode_clear(tree->root);
	free(tree);
}

// Função para printar cada nó da árvore
void bstNode_print(bstNode* root) {
	printf("<");
	if (root) {
		printf("%d", root->value);
		bstNode_print(root->left);
		bstNode_print(root->right);
	}
	printf(">");
}

// Função para printar a árvore
void bsTree_print(bsTree* tree) {
	bstNode_print(tree->root);
	printf("\n");
}

// Função para calcular o maior entre dois valores
int bigger(int x, int y){
  return (x > y) ? x : y;
}

// Função para calcular a altura de um nó
int bstNode_height(bstNode* root) {
  if (!root){
    return -1;
  } else {
    return bigger(bstNode_height(root->left), bstNode_height(root->right)) + 1;
  }
}

// Função para calcular a altura da árvore
int bsTree_height(bsTree* tree) {
  return bstNode_height(tree->root);
}

// Função para buscar um valor nó a nó
// Método = Pré-ordem (raiz, esquerda, direita)
bstNode* bstNode_find(bstNode* root, int value) {
	if (!root) {
		return NULL;
	} else if (root->value == value) {
		// Verifica a raiz
		return root;
	} else if (root->value > value) {
		// value é menor que a raiz, vamos para a esquerda
		return bstNode_find(root->left, value);
	} else {
		// value é maior que a raiz, vamos para a direita
		return bstNode_find(root->right, value);
	}
}

// Função para buscar um valor na árvore
bstNode* bsTree_find(bsTree* tree, int value) {
	return bstNode_find(tree->root, value);
}