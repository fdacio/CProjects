#include "t_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void randomize_array(int *array, int size) {
  int used[101] = {0};
  srand((unsigned)time(NULL));
  for (int i = 0; i < size; i++) {
    int value;
    do {
      value = rand() % 100 + 1;
    } while (used[value]);
    used[value] = 1;
    array[i] = value;
  }
}