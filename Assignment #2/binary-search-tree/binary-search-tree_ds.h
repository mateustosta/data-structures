typedef struct node bstNode;
typedef struct tree bsTree;

// Estrutura para armazenar os nós da árvore
struct node {
	int value;
	bstNode* left;
	bstNode* right;
};

// Estrutura para armazenar a raiz da árvore
struct tree {
	bstNode* root;
};

bsTree* bsTree_create(void);
void bsTree_insert(bsTree* tree, int value);
void bsTree_remove(bsTree* tree, int value);
void bsTree_clear(bsTree* tree);
void bsTree_print(bsTree* tree);
bstNode* bstNode_find(bstNode* root, int value);
bstNode* bsTree_find(bsTree* tree, int value);
