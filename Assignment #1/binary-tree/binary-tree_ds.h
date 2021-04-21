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

bTree* bTree_create(btNode* root);
btNode* bTree_create_node(int value, btNode* left, btNode* right);
void bTree_clear(bTree* tree);
void bTree_print(bTree* tree);
int btNode_height(btNode* root);
int bTree_height(bTree* root);
btNode* bTree_find(bTree* tree, int value);