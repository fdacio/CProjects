/* Testes para as funções de pilha */
/*** Compile and build: gcc test.c src/stack.c src/s_utils.c -Iinclude -o build/test  ****/
/*** Execute: ./build/test ****/

#include "stack.h"
#include "s_utils.h"
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

  printf("\n--- push ---\n");

  TItemStack *topStack = NULL;

  TItemStack *i1 = new_item_stack("Soma");
  TItemStack *i2 = new_item_stack("Multiplicacao");
  TItemStack *i3 = new_item_stack("Subtracao");
  TItemStack *i4 = new_item_stack("Divisao");

  push(i1, &topStack);
  push(i2, &topStack);
  push(i3, &topStack);
  push(i4, &topStack);

  char text1[50], text2[50], text3[50], text4[50];
  snprintf(text1, sizeof(text1), "Push Item 1 %s", i1->name);
  snprintf(text2, sizeof(text2), "Push Item 2 %s", i2->name);
  snprintf(text3, sizeof(text3), "Push Item 3 %s", i3->name);
  snprintf(text4, sizeof(text4), "Push Item 4 %s", i4->name);

  TEST(text1, strcmp(topStack->name, i4->name) == 0);
  TEST(text2, strcmp(topStack->prev->name, i3->name) == 0);
  TEST(text3, strcmp(topStack->prev->prev->name, i2->name) == 0);
  TEST(text4, strcmp(topStack->prev->prev->prev->name, i1->name) == 0);

  print_stack(topStack);

  free_stack(topStack);
}

void test_push_stack_overflow() {

  printf("\n--- push with stackoverflow (Max 4) ---\n");

  TItemStack *topStack = NULL;

  TItemStack *i1 = new_item_stack("Soma");
  TItemStack *i2 = new_item_stack("Multiplicacao");
  TItemStack *i3 = new_item_stack("Subtracao");
  TItemStack *i4 = new_item_stack("Divisao");
  TItemStack *i5 = new_item_stack("Fatorial");

  push(i1, &topStack);
  push(i2, &topStack);
  push(i3, &topStack);
  push(i4, &topStack);
  push(i5, &topStack);

  TEST("Push stack overflow", strcmp(topStack->name, i5->name) != 0);

  free_stack(topStack);
}

void test_pop() {

  printf("\n--- pop ---\n");

  TItemStack *topStack = NULL;

  TItemStack *i1 = new_item_stack("Soma");
  TItemStack *i2 = new_item_stack("Multiplicacao");

  push(i1, &topStack);
  push(i2, &topStack);
  print_stack(topStack);

  TItemStack *pop1 = pop(&topStack);

  char text1[50];
  snprintf(text1, sizeof(text1), "Push Item %s", i2->name);

  TEST(text1, (strcmp(pop1->name, i2->name) == 0));

  free_stack(topStack);
}

void test_pop_empty_stack() {

  printf("\n--- pop stack empty---\n");

  TItemStack *topStack = NULL;

  TItemStack *i1 = new_item_stack("Soma");
  TItemStack *i2 = new_item_stack("Multiplicacao");

  push(i1, &topStack);
  push(i2, &topStack);

  TItemStack *pop1 = pop(&topStack);
  TItemStack *pop2 = pop(&topStack);
  TItemStack *popNull = pop(&topStack);

  TEST("Pop empty stack", popNull == NULL);

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
  test_push_stack_overflow();
  test_pop();
  test_pop_empty_stack();
  test_free_stack();

  printf("\n===========================\n");
  printf("FIM DOS TESTES - stack.c");
  printf("\n===========================\n\n");
  return 0;
}
