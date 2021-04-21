#include <stdio.h>
#include <stdlib.h>
#include "avl-tree_ds.h"

int main() {
	// Cria a árvore
	avlTree* avlTree = avlTree_create();

	/*
	Insere elementos na árvore
	Se inserirmos 5, 3, 2 nessa ordem,
	a árvore deve ser printada (inorder) como
	2, 3, 5

	árvore após inserções
            5
           /
          3
         /
        2
	como é AVL, será balanceada, após balanceamento
            3
           / \
          2   5

	O código está configura para printar as rotações quando
	elas forem feitas, neste exemplo, deve ser printado, uma vez
	RotationLL. Caso queira desabilitar estes prints, basta remover,
	ou comentar os mesmos em cada função de rotação.
	*/
	avlTree_insert(avlTree, 5);
	avlTree_insert(avlTree, 3);
	avlTree_insert(avlTree, 2);

	// Imprime a árvore inorder
	printf("========AVL Tree Inicial Inorder========\n");
	avlTree_inorder(avlTree);
	printf("========================================\n\n");

	// Imprime a árvore preorder
	// Esperado: 3, 2, 5
	printf("========AVL Tree Inicial Preorder========\n");
	avlTree_preorder(avlTree);
	printf("=========================================\n\n");

	// Adiciona mais 3 nós
	avlTree_insert(avlTree, 10);
	avlTree_insert(avlTree, 9);
	avlTree_insert(avlTree, 8);

	/*
	Resultado esperado SEM balanceamento
                3
               / \
              2   5
                   \
                   10
                   /
                  9
                 /
                8
	Com balanceamento
                5
               / \
              3   9
             /   / \
            2   8  10
	Além disso, esperamos que seja printado
	RotationLL
	RotationRR
	RotationLL
	RotationRR

	Por fim, o print inorder deve ser
	2 3 5 8 9 10
	*/

	// Imprime a árvore inorder
	printf("========AVL Tree Com 8,9,10 Inorder========\n");
	avlTree_inorder(avlTree);
	printf("===========================================\n\n");

	/*
	Removendo elementos da árvore
	Resultado esperado
                5
               / \
              3   8
             /     \
            2      10
	Sem rotações necessárias
	Print inorder: 2, 3, 5, 8, 10
	*/
	avlTree_remove(avlTree, 9);

	// Imprime a árvore inorder
	printf("========AVL Tree Removendo 9 Inorder========\n");
	avlTree_inorder(avlTree);
	printf("============================================\n\n");

	// Verifica se está vazia (1 - está / 0 - não está)
	printf("Empty: %d\n", avlTree_empty(avlTree));

	// Procura e printa um elemento (0 - não encontrou / 1 - encontrou)
	printf("Find element: %d\n", avlTree_find_element(avlTree, 120));
	
	// Calcula a altura da ávore (0 se vazia)
	printf("Height: %d\n", avlTree_height(avlTree));

	// Libera a memória alocada para a árvore
	avlTree_clear(avlTree);
}