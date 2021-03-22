typedef struct node* bTree;

bTree* bTree_create();
void bTree_clear(bTree* root);
int bTree_insert(bTree* root, int value);
int bTree_remove(bTree* root, int value);
int bTree_empty(bTree* root);
void bTree_preorder(bTree* root);
void bTree_inorder(bTree* root);
void bTree_postorder(bTree* root);
int bTree_find_element(bTree* root, int value);