#include <stdio.h>
#include <stdlib.h>
#include "binary-search-tree_ds.h"

int main() {
	// Cria a árvore
	bsTree* tree = bsTree_create();

	// Insere valores
	bsTree_insert(tree, 1);
	bsTree_insert(tree, 4);
	bsTree_insert(tree, 5);

	// Printa a árvore preorder
	bsTree_print(tree);

	// Remove o 5
	bsTree_remove(tree, 5);

	// Printa a árvore preorder
	bsTree_print(tree);
	
	// Procura e printa um valor (NULL se não encontrar, printa -999)
	bstNode* node = bsTree_find(tree, 121);
	printf("Find: %d\n", node != NULL ? node->value : -999);

	// Calcula e printa a altura da árvore (-1 se for vazia)
	printf("Tree's Height: %d\n", bsTree_height(tree));

	// Calcula e printa a altura de um nó (-1 se o nó não existir)
	printf("Node's Height: %d\n", bstNode_height(node));

	// Libera a memória
	bsTree_clear(tree);

	return 0;
}