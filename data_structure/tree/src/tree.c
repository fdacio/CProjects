/** binary tree representation */

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Create a new node with the specified data.
 * @param data The data to be stored in the node.
 */
TNode *create_node(const char *data) {
  TNode *new_node = (TNode *)malloc(sizeof(TNode));
  if (new_node == NULL) {
    perror("malloc failed");
    return NULL;
  }
  strcpy(new_node->data, data);
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

/** 
 * Insert a node with the specified data into the binary tree.
 * @param root Pointer to the root of the tree.
 * @param data The data to be inserted.
 */
void insert_node(TNode **root, const char *data) {
  if (*root == NULL) {
    *root = create_node(data);
    return;
  }
  if (strcmp(data, (*root)->data) > 0) {
    insert_node(&(*root)->right, data);
  } else {
    insert_node(&(*root)->left, data);
  }
}

/** 
 * Os nós são visitados antes dos filhos, ou seja, 
 * a raiz é processada primeiro, seguida pela subárvore esquerda e depois pela subárvore direita.
 * @param root Ponteiro para a raiz da árvore.
 */
void pre_order(TNode *root) {
  if (root != NULL) {
    printf("%s ", root->data);
    pre_order(root->left);
    pre_order(root->right);

  }
}

/** 
 * Os nós são visitados em ordem, ou seja, a subárvore esquerda é processada primeiro, 
 * seguida pela raiz e depois pela subárvore direita.
 * @param root Ponteiro para a raiz da árvore.
 */
void in_order(TNode *root) {
  if (root != NULL) {
    in_order(root->left);
    printf("%s ", root->data);
    in_order(root->right);
  }
}

/**
 * Os nós são visitados após os filhos, ou seja, a subárvore esquerda é processada primeiro,
 * seguida pela subárvore direita e depois pela raiz.
 * @param root Ponteiro para a raiz da árvore.
 */
void post_order(TNode *root) {
  if (root != NULL) {
    post_order(root->left);
    post_order(root->right);
    printf("%s ", root->data);
  }
}


/**
 * Search for a node with the specified data in the binary tree.
 * @param root Pointer to the root of the tree.
 * @param data The data to search for.
 * @return Pointer to the node if found, otherwise NULL.
 */
TNode *search_node(TNode *root, const char *data) {
  if (root == NULL || strcmp(root->data, data) == 0) {
    return root;
  }
  if (strcmp(data, root->data) < 0) {
    return search_node(root->left, data);
  } else {
    return search_node(root->right, data);
  }
}

/**
 * Remove a node with the specified data from the binary tree.
 * @param root Pointer to the root of the tree.
 * @param data The data of the node to be removed.
 */
void remove_node(TNode **root, const char *data) {
  if (*root == NULL) {
    return;
  }
  if (strcmp(data, (*root)->data) < 0) {
    remove_node(&(*root)->left, data);
  } else if (strcmp(data, (*root)->data) > 0) { 
    remove_node(&(*root)->right, data);
  } else {// Nesse ponto encontramos o nó a ser removido
    // Node with only one child or no child
    if ((*root)->left == NULL) {
      TNode *temp = (*root)->right;
      free(*root);
      *root = temp;
    } else if ((*root)->right == NULL) {
      TNode *temp = (*root)->left;
      free(*root);
      *root = temp;
    } else {
      // Node with two children: Get the inorder successor
      TNode *temp = (*root)->right;
      while (temp->left != NULL) {
        temp = temp->left;
      }
      strcpy((*root)->data, temp->data); // Copy the inorder successor's content to this node
      remove_node(&(*root)->right, temp->data); // Delete the inorder successor
    }
  }
}

/**
 * Free the memory allocated for the binary tree.
 * @param root Pointer to the root of the tree.
 */
void free_tree(TNode *root) {
  if (root != NULL) {
    free_tree(root->left);
    free_tree(root->right);
    free(root);
  }
}
