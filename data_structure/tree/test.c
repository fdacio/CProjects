#include "tree.h"
#include "t_utils.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

  printf("\n=============================\n");
  printf("TESTES - tree.c");
  printf("\n=============================\n");

  TNode *root = NULL;

  int data_values[10];
  randomize_array(data_values, 10);
  int len = sizeof(data_values) / sizeof(data_values[0]);
  printf("Valores: ");
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

  printf("Níveis: ");
  print_tree(root, 2);
  printf("\n");


  int search_values[] = {5, 15, 100};
  for (int i = 0; i < 3; i++) {
    int data = search_values[i];
    TNode *result = search_node(root, data);
    if (result != NULL) { 
      printf("Valor %d encontrado na árvore.\n", data);
    } else {
      printf("Valor %d não encontrado na árvore.\n", data);
    }
  }

  free_tree(root);

  printf("\n=============================\n");
  printf("FIM DOS TESTES - tree.c");
  printf("\n=============================\n\n");

  return 0;

}
