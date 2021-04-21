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
	printf("%d\n", node != NULL ? node->value : -999);

	// Libera a memória
	bsTree_clear(tree);

	return 0;
}