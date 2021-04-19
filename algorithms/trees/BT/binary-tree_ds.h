typedef struct node btNode;
typedef struct tree bTree;

bTree* bTree_create(btNode* root);
btNode* bTree_create_node(int value, btNode* left, btNode* right);

void btNode_clear(btNode* root);
void bTree_clear(bTree* tree);

void btNode_print(btNode* root);
void bTree_print(bTree* tree);

btNode* btNode_find(btNode* root, int value);
btNode* bTree_find(bTree* tree, int value);