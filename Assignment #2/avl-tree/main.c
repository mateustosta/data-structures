#include <stdio.h>
#include "avl-tree_ds.h"

int main(){
  int result, i;
  int N = 10, data[10] = {1,2,3,10,4,5,9,7,8,6};

  // Cria a árvore
  bTree* avl_tree;
  avl_tree = bTree_create();

  // Preenche a árvore
  for (i = 0; i < N; i++) {
    result = bTree_insert(avl_tree, data[i]);
  }

  printf("\n\t\tAVL TREE PREORDER:\n");
  bTree_preorder(avl_tree);
  printf("\n\n");

  printf("\n\t\tAVL TREE INORDER:\n");
  bTree_inorder(avl_tree);
  printf("\n\n");

  printf("\n\t\tAVL TREE POSTORDER:\n");
  bTree_postorder(avl_tree);
  printf("\n\n");

  printf("\n\t\tREMOVING ELEMENTS\n");
  bTree_remove(avl_tree, 6);
  printf("\n\t\tAVL TREE PREORDER:\n");
  bTree_preorder(avl_tree);
  printf("\n\n");
  bTree_remove(avl_tree, 7);
  printf("\n\t\tAVL TREE PREORDER:\n");
  bTree_preorder(avl_tree);
  printf("\n\n");
  bTree_remove(avl_tree, 4);
  printf("\n\t\tAVL TREE PREORDER:\n");
  bTree_preorder(avl_tree);
  printf("\n\n");

  printf("\n\t\tFINDING ELEMENTS\n");
  printf("Is 2 on tree? %d\n", bTree_find_element(avl_tree, 2));  
  printf("Is 4 on tree? %d\n", bTree_find_element(avl_tree, 4));  


  // Libera a árvore
  bTree_clear(avl_tree);

  return 0;
}
