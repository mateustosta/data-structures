typedef struct node bstNode;
typedef struct tree bsTree;

bsTree* bsTree_create(void);

bstNode* bstNode_insert(bstNode* root, int value);
void bsTree_insert(bsTree* tree, int value);

bstNode* bstNode_remove(bstNode* root, int value);
void bsTree_remove(bsTree* tree, int value);

void bstNode_clear(bstNode* root);
void bsTree_clear(bsTree* tree);

void bstNode_print(bstNode* root);
void bsTree_print(bsTree* tree);

bstNode* bstNode_find(bstNode* root, int value);
bstNode* bsTree_find(bsTree* tree, int value);
