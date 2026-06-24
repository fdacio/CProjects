#ifndef TREE_H
#define TREE_H

typedef struct node_tree {
    char data[100]; // Assuming a maximum length of 100 for the string data
    struct node_tree *left;
    struct node_tree *right;
} TNode;

TNode* create_node(const char *data);
void insert_node(TNode **root, const char *data);
void remove_node(TNode **root, const char *data);
void pre_order(TNode *root);
void in_order(TNode *root);
void post_order(TNode *root);
TNode* search_node(TNode *root, const char *data);
void free_tree(TNode *root);

#endif
