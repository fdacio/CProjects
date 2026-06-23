/* Testes para as funções de árvore */
/*** Compile and build: gcc test.c src/tree.c src/t_utils.c -Iinclude -o
 * build/test  ****/
/*** Execute: ./build/test ****/

#include "t_utils.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

// Macro auxiliar para exibir resultado
#define TEST(nome, condicao)                                                   \
  do {                                                                         \
    if (condicao)                                                              \
      printf( "OK - PASSOU: %s\n", nome);                                         \
    else                                                                       \
      printf("ERROR - FALHOU: %s\n", nome);                                         \
  } while (0)



void test_add_only_one_node(void) {
  printf("Teste de apenas 1 nó\n");
  TNode *root = NULL;
  insert_node(&root, 10);
  TNode *node_10 = search_node(root, 10);
  TEST("Nó 10 left NULL e right NULL",
       node_10 != NULL && 
       node_10->data == 10 && 
       node_10->left == NULL &&
       node_10->right == NULL);
  printf("\n");
  free_tree(root);
}   

void test_add_multiple_nodes(TNode *root) {
  printf("Teste de adicionar múltiplos nós\n");
  TNode *node_50 = search_node(root, 50);
  TEST("Nó 50 encontrado", node_50 != NULL && node_50->data == 50);
  TNode *node_left_50 = node_50 != NULL ? node_50->left : NULL;
  TEST("Nó left 50: 30 encontrado", node_left_50 != NULL && node_left_50->data == 30);
  TNode *node_right_50 = node_50 != NULL ? node_50->right : NULL;
  TEST("Nó right 50: Nó 70 encontrado", node_right_50 != NULL && node_right_50->data == 70);
  printf("\n");
}

void test_search_existent_node(TNode *root) {
  printf("Teste de busca por nó existente\n");
  TNode *node_60 = search_node(root, 60);
  TEST("Nó 60 encontrado", node_60 != NULL && node_60->data == 60);
  printf("\n");
}

void test_search_non_existent_node(TNode *root) {
  printf("Teste de busca por nó inexistente\n");
  TNode *node_100 = search_node(root, 100);
  TEST("Nó 100 não encontrado", node_100 == NULL);
  printf("\n");
}

void test_remove_node(TNode *root) {
  printf("Teste de remoção de nó\n");
  remove_node(&root, 30);
  TNode *node_30_dont_searched = search_node(root, 30);
  TEST("Nó 30 removido", node_30_dont_searched == NULL);
  printf("\n");
}

void test_remove_non_existent_node(TNode *root) {
  printf("Teste de remoção de nó inexistente\n");
  remove_node(&root, 100); // Tentativa de remover nó inexistente
  TNode *node_10 = search_node(root, 10);
  TEST("Nó 10 ainda existe", node_10 != NULL && node_10->data == 10);
  printf("\n");
}

void test_remove_node_with_two_children(TNode *root) {
  printf("Teste de remoção de nó com dois filhos\n"); 
  remove_node(&root, 50);
  TNode *node_50_dont_searched = search_node(root, 50);
  TEST("Nó 50 removido", node_50_dont_searched == NULL);
  printf("\n");
}

void test_remove_node_with_one_child(TNode *root) {
  printf("Teste de remoção de nó com um filho\n");
  remove_node(&root, 20);
  TNode *node_20_dont_searched = search_node(root, 20);
  TEST("Nó 20 removido", node_20_dont_searched == NULL);
  printf("\n");
}

void test_remove_leaf_node(TNode *root) {
  printf("Teste de remoção de nó folha\n");
  remove_node(&root, 10);
  TNode *node_10_dont_searched = search_node(root, 10);
  TEST("Nó folha 10 removido", node_10_dont_searched == NULL);
  printf("\n");
}

void test_free_tree(TNode *root) {
  printf("Teste de liberacao de memoria(free) da arvore\n");
  free_tree(root);
  TEST("Arvore liberada", 1);
  printf("\n");
}

void test_in_order_traversal(TNode *root) {
  printf("Teste de travessia in-order: ");
  in_order(root);
  printf("\n");
}

void test_pre_order_traversal(TNode *root) {
  printf("Teste de travessia pre-order: ");
  pre_order(root);
  printf("\n");
}

void test_post_order_traversal(TNode *root) {
  printf("Teste de travessia post-order: ");
  post_order(root);
  printf("\n");
}

void test_print_tree(TNode *root) {
  print_tree(root, 2);
  printf("\n");
}

int main() {

  printf("\n=============================\n");
  printf("TESTES - tree.c");
  printf("\n=============================\n");

  TNode *root = NULL;
  int data_values[] = {50, 30, 70, 80, 20, 85, 40, 60, 90, 10, 35, 45, 65};
  int len = sizeof(data_values) / sizeof(data_values[0]);
  printf("Dados: ");
  for (int i = 0; i < len; i++) {
    int value = data_values[i];
    printf("%d ", value);
    insert_node(&root, value);
  }

  printf("\n");
  printf("Root after insertions: %d\n", root->data);
  printf("\n");

  // test_add_only_one_node();
  
  // test_add_multiple_nodes(root);

  // test_print_tree(root);

  // test_search_existent_node(root);

  // test_search_non_existent_node(root);

  test_pre_order_traversal(root);
  test_in_order_traversal(root);
  test_post_order_traversal(root);
  
  // test_remove_node(root);

  // test_print_tree(root);

  // test_remove_node_with_two_children(root);

  // test_print_tree(root);

  // test_remove_node_with_one_child(root);

  // test_print_tree(root);

  // test_remove_leaf_node(root);

  // test_print_tree(root);

  test_free_tree(root);

  printf("\n=============================\n");
  printf("FIM DOS TESTES - tree.c");
  printf("\n=============================\n\n");

  return 0;
}
