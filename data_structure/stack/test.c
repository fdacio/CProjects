/* Testes para as funções de pilha */

/*** Compile and build: gcc test.c src/stack.c src/s_utils.c -Iinclude -o build/test  ***/
/*** Execute: ./build/test ***/

#include "s_utils.h"
#include "stack.h"
#include <stdio.h>
#include <string.h>

// Macro auxiliar para exibir resultado
#define TEST(nome, condicao)                                                   \
  do {                                                                         \
    if (condicao)                                                              \
      printf("✅ PASSOU: %s\n", nome);                                         \
    else                                                                       \
      printf("❌ FALHOU: %s\n", nome);                                         \
  } while (0)

void test_new_item() {
  printf("\n--- new_item ---\n");
  TItemStack *item = new_item_stack("12345678901234567890");
  int _b = (strcmp(item->name, "1234567890123456789") == 0) && (item->prev == NULL);
  TEST("New Item", _b);
}

void test_push() {

  printf("\n--- push - Max(4)---\n");

  TItemStack *topStack = NULL;

  TItemStack *i1 = new_item_stack("Soma");
  push(i1, &topStack);

  TEST("Push Item 1 - Soma", strcmp(topStack->name, "Soma") == 0);
  print_stack(topStack);

  TItemStack *i2 = new_item_stack("Multiplicacao");
  push(i2, &topStack);
  TEST("Push Item 2 - Multiplicacao", strcmp(topStack->name, "Multiplicacao") == 0);
  print_stack(topStack);

  TItemStack *i3 = new_item_stack("Subtracao");
  push(i3, &topStack);
  TEST("Push Item 3 - Subtracao", strcmp(topStack->name, "Subtracao") == 0);
  print_stack(topStack);

  TItemStack *i4 = new_item_stack("Divisao");
  push(i4, &topStack);
  TEST("Push Item 4 - Divisao", strcmp(topStack->name, "Divisao") == 0);
  print_stack(topStack);

  TItemStack *i5 = new_item_stack("Fatorial");
  push(i5, &topStack);
  TEST("Push Item 5 - Fatorial - stack overflow", strcmp(topStack->name, "Divisao") == 0);
  print_stack(topStack);

  free_stack(topStack);
}

void test_pop() {

  printf("\n--- pop ---\n");

  TItemStack *topStack = NULL;
  TItemStack *i1 = new_item_stack("Soma");
  TItemStack *i2 = new_item_stack("Multiplicacao");
  TItemStack *i3 = new_item_stack("Subtracao");
  TItemStack *i4 = new_item_stack("Divisao");
  push(i1, &topStack);
  push(i2, &topStack);
  push(i3, &topStack);
  push(i4, &topStack);

  print_stack(topStack);

  TItemStack *pop1 = pop(&topStack);
  TEST("Pop Item 1 - Divisao", (strcmp(pop1->name, "Divisao") == 0));
  print_stack(topStack);

  TItemStack *pop2 = pop(&topStack);
  TEST("Pop Item 2 - Subtracao", (strcmp(pop2->name, "Subtracao") == 0));
  print_stack(topStack);

  TItemStack *pop3 = pop(&topStack);
  TEST("Pop Item 3 - Multiplicacao", (strcmp(pop3->name, "Multiplicacao") == 0));
  print_stack(topStack);  

  TItemStack *pop4 = pop(&topStack);
  TEST("Pop Item 4 - Soma", (strcmp(pop4->name, "Soma") == 0));
  print_stack(topStack);  

  TItemStack *pop5 = pop(&topStack);
  TEST("Pop Item 5 - stack vazia", (pop5 == NULL));
  print_stack(topStack);

  free_stack(topStack);
}


void test_free_stack() {
  printf("\n--- free_stack ---\n");

  // caso 1: stack com vários itens
  TItemStack *topStack1 = NULL;
  TItemStack *i1 = new_item_stack("Soma");
  TItemStack *i2 = new_item_stack("Multiplicacao");
  TItemStack *i3 = new_item_stack("Subtracao");
  push(i1, &topStack1);
  push(i2, &topStack1);
  push(i3, &topStack1);
  free_stack(topStack1);
  TEST("free stack com 3 itens sem crash", 1); // se chegou aqui, não crashou

  // caso 2: stack com vários itens
  TItemStack *topStack2 = NULL;
  TItemStack *i4 = new_item_stack("Divisao");
  push(i4, &topStack2);
  free_stack(topStack2);
  TEST("free stack com 1 item sem crash", 1); // se chegou aqui, não crashou

  // caso 3: stack sem itens
  TItemStack *topStack3 = NULL;
  free_stack(topStack3);
  TEST("free stack sem item ", 1); // se chegou aqui, não crashou
}

int main(void) {
  printf("\n=============================\n");
  printf("TESTES - stack.c");
  printf("\n=============================\n");

  test_new_item();
  test_push();
  test_pop();
  test_free_stack();

  printf("\n===========================\n");
  printf("FIM DOS TESTES - stack.c");
  printf("\n===========================\n\n");
  return 0;
}
