#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

  printf("\n=============================\n");
  printf("TESTES - tree.c");
  printf("\n=============================\n");

  TNode *root = NULL;

  int data_values[] = {84, 3,  7,  9,  5,  6,  8,  1,  2,  0,  21, 93,
                       12, 11, 10, 15, 14, 13, 20, 19, 18, 17, 16, 4};
  int len = sizeof(data_values) / sizeof(data_values[0]);                     
  for (int i = 0; i < len; i++) {
    int data = data_values[i];
    printf("%d ", data);
    insert_node(&root, data);
  }
  printf("\n");

  printf("Pre-order: ");
  pre_order(root);
  printf("\n");

  printf("In-order: ");
  in_order(root);
  printf("\n");

  printf("Post-order: ");
  post_order(root);
  printf("\n");

  free_tree(root);

  TNode *_root = NULL;

  for (int i = 0; i < 100000; i++) {
    insert_node(&_root, i);
  }

  
  int search_values[] = {5, 15, 100};
  for (int i = 0; i < 3; i++) {
    int data = search_values[i];
    TNode *result = search_node(_root, data);
    if (result != NULL) { 
      printf("Valor %d encontrado na árvore.\n", data);
    } else {
      printf("Valor %d não encontrado na árvore.\n", data);
    }
  }

  free_tree(_root);


  printf("\n=============================\n");
  printf("FIM DOS TESTES - tree.c");
  printf("\n=============================\n\n");

  return 0;

}
