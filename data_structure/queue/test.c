/* Testes para as funções de fila */
/*** Compile and build: gcc test.c src/queue.c src/q_utils.c -Iinclude -o build/test  ****/
/*** Execute: ./build/test ****/

#include "queue.h"
#include "q_utils.h"
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

  TItemQueue *item = new_item_queue("Arquivo 1");
  int _b = (strcmp(item->name, "Arquivo 1") == 0) && (item->next == NULL);
  TEST("New Item", _b);
}  

void test_enqueue() {
  printf("\n--- test enqueue (Max: %u) ---\n", 4);

  TItemQueue *iniQueue = NULL;
  TItemQueue *endQueue = NULL;

  // caso 1 - Primerio item da fila
  TItemQueue *i1 = new_item_queue("Arquivo 1");
  enqueue(i1, &iniQueue, &endQueue);
  TEST("Enqueue item Arquivo 1", (strcmp(iniQueue->name, i1->name) == 0) && (strcmp(endQueue->name, i1->name) == 0));
  print_queue(iniQueue);
  

  // caso 2 - Segundo item da fila
  TItemQueue *i2 = new_item_queue("Arquivo 2");
  enqueue(i2, &iniQueue, &endQueue);
  TEST("Enqueue item Arquivo 2", (strcmp(iniQueue->name, i1->name) == 0) && (strcmp(endQueue->name, i2->name) == 0));
  print_queue(iniQueue);


  // caso 3 - Terceiro item da fila
  TItemQueue *i3 = new_item_queue("Arquivo 3");
  enqueue(i3, &iniQueue, &endQueue);
  TEST("Enqueue item Arquivo 3", (strcmp(iniQueue->name, i1->name) == 0) && (strcmp(endQueue->name, i3->name) == 0));
  print_queue(iniQueue);

  
  // caso 4 - Quarto item da fila
  TItemQueue *i4 = new_item_queue("Arquivo 4");
  enqueue(i4, &iniQueue, &endQueue);
  TEST("Enqueue item Arquivo 4", (strcmp(iniQueue->name, i1->name) == 0) && (strcmp(endQueue->name, i4->name) == 0));
  print_queue(iniQueue);

  // caso 5 - Fila cheia
  TItemQueue *i5 = new_item_queue("Arquivo 5");
  enqueue(i5, &iniQueue, &endQueue);
  TEST("Enqueue em fila cheia", (strcmp(iniQueue->name, i1->name) == 0) && (strcmp(endQueue->name, i5->name) != 0));
  print_queue(iniQueue);

  free_queue(iniQueue);
}

void test_dequeue() {
  printf("\n----- test dequeue -----\n");

  TItemQueue *iniQueue = NULL;
  TItemQueue *endQueue = NULL;

  TItemQueue *i1 = new_item_queue("Arquivo 1");
  TItemQueue *i2 = new_item_queue("Arquivo 2");
  TItemQueue *i3 = new_item_queue("Arquivo 3");
  TItemQueue *i4 = new_item_queue("Arquivo 4");
  enqueue(i1, &iniQueue, &endQueue);
  enqueue(i2, &iniQueue, &endQueue);
  enqueue(i3, &iniQueue, &endQueue);
  enqueue(i4, &iniQueue, &endQueue);

  print_queue(iniQueue);

  // caso 1 - Dequeue item Arquivo 1
  TItemQueue *d1 = dequeue(&iniQueue, &endQueue);
  TEST("Dequeue item Arquivo 1", (strcmp("Arquivo 1", d1->name) == 0));
  print_queue(iniQueue);

  // caso 2 - Dequeue item Arquivo 2
  TItemQueue *d2 = dequeue(&iniQueue, &endQueue);
  TEST("Dequeue item Arquivo 2", (strcmp("Arquivo 2", d2->name) == 0));
  print_queue(iniQueue);

  // caso 3 - Dequeue item Arquivo 3
  TItemQueue *d3 = dequeue(&iniQueue, &endQueue);
  TEST("Dequeue item Arquivo 3", (strcmp("Arquivo 3", d3->name) == 0));
  print_queue(iniQueue);

  // caso 4 - Dequeue item Arquivo 4 (último item da fila)
  TItemQueue *d4 = dequeue(&iniQueue, &endQueue);
  TEST("Dequeue item Arquivo 4 (Último item da fila)", (strcmp("Arquivo 4", d4->name) == 0));
  print_queue(iniQueue);

  // caso 5 - Dequeue item Arquivo 5
  TItemQueue *d5 = dequeue(&iniQueue, &endQueue);
  TEST("Dequeue item em Fila vazia", d5 == NULL);
  print_queue(iniQueue);

  free_queue(iniQueue);
}

void test_free_queue() {
  printf("\n--- free_queue ---\n");

  // caso 1: queue com vários itens
  TItemQueue *iniQueue = NULL;
  TItemQueue *endQueue = NULL;
  TItemQueue *i1 = new_item_queue("Arquivo 1");
  TItemQueue *i2 = new_item_queue("Arquivo 2");
  TItemQueue *i3 = new_item_queue("Arquivo 3");
  enqueue(i1, &iniQueue, &endQueue);
  enqueue(i2, &iniQueue, &endQueue);
  enqueue(i3, &iniQueue, &endQueue);
  free_queue(iniQueue);
  TEST("free queue com 3 itens sem crash", 1); // se chegou aqui, não crashou

  // caso 2: queue com vários itens
  TItemQueue *iniQueue2 = NULL;
  TItemQueue *endQueue2 = NULL;
  TItemQueue *i4 = new_item_queue("Arquivo 4");
  enqueue(i4, &iniQueue2, &endQueue2);
  free_queue(iniQueue2);
  TEST("free queue com 1 item sem crash", 1); // se chegou aqui, não crashou
  
  // caso 3: queue sem itens
  TItemQueue *iniQueue3 = NULL;
  free_queue(iniQueue3);
  TEST("free queue sem item ", 1); // se chegou aqui, não crashou

}

int main(void) {
  printf("=============================\n");
  printf("     TESTES - queue.c        \n");
  printf("=============================\n");

  test_new_item();
  test_enqueue();
  test_dequeue();
  test_free_queue();

  printf("\n===========================\n");
  printf("    FIM DOS TESTES - queue.c \n");
  printf("=============================\n");

  return 0;
}
