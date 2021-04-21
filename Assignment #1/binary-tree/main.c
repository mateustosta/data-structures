#include <stdio.h>
#include <stdlib.h>
#include "binary-tree_ds.h"

int main() {
	// Cria uma árvore
	bTree* tree = bTree_create(
		bTree_create_node(1, 
			bTree_create_node(2, 
				NULL,
				bTree_create_node(4, NULL, NULL)
				),
			bTree_create_node(3,
				bTree_create_node(5, NULL, NULL),
				bTree_create_node(6, NULL, NULL)
				)
			)
		);	

	// Printa a árvore
	bTree_print(tree);
	printf("\n");

	// Procura e printa um valor na árvore (NULL se não encontrar, printa -999)
	btNode* node = bTree_find(tree, 112);
	printf("%d\n", node != NULL ? node->value : -999);

	// Libera a memória
	bTree_clear(tree);

	return 0;
}
