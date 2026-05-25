#ifndef TREE_H
#define TREE_H

typedef struct node_tree {
    int data;
    struct node_tree *left;
    struct node_tree *right;
} TNode;

TNode* create_node(int data);
void insert_node(TNode **root, int data);
void pre_order(TNode *root);
void in_order(TNode *root);
void post_order(TNode *root);
TNode* search_node(TNode *root, int data);
void free_tree(TNode *root);

#endif
