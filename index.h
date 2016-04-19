#ifndef INDEX_H
#define INDEX_H

int cmpstr(const void* a, const void* b);
void cria_primeiro_indice(char arq[]);
void cria_segundo_indice(char ind[]);

//árvore

struct bin_tree {
    char data[11];
    struct bin_tree * right, * left;
};
typedef struct bin_tree node;

void insert(node ** tree, char *c);

void print_inorder(node * tree);

void deltree(node * tree);
node* search(node ** tree, char *c);

node* newNode(char *data);
node* sortedArrayToBST(char arr[], int start, int end);



#endif
