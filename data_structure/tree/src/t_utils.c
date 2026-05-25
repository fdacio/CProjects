#include "t_utils.h"
#include <stdio.h>

void print_tree(TNode *root, int space) {
  if (root == NULL) {
    return;
  }
  space += 10;
  print_tree(root->right, space);
  printf("\n");
  for (int i = 10; i < space; i++) {
    printf(" ");
  }
  printf("%d\n", root->data);
  print_tree(root->left, space);
}
