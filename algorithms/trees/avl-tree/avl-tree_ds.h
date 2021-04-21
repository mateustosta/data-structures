typedef struct node* avlTree;

// Struct para armazenar os nós da árvore
struct node {
    int value;
    int height;
    struct node* left;
    struct node* right;
};

avlTree* avlTree_create();
void avlTree_clear(avlTree* root);
int avlTree_insert(avlTree* root, int value);
int avlTree_remove(avlTree* root, int value);
int avlTree_empty(avlTree* root);
void avlTree_preorder(avlTree* root);
void avlTree_inorder(avlTree* root);
void avlTree_postorder(avlTree* root);
int avlTree_height(avlTree* root);
int avlTree_find_element(avlTree* root, int value);