#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/**
 * Função para imprimir o conteúdo da pilha.
 * @param topStack Ponteiro para o topo da pilha.
 */
void print_stack(TItemStack *topStack) {
  TItemStack *aux = topStack;
  printf("%-20s | %6s | %16s | %16s\n", "Name", "Count", "Address", "Prev");
  printf("-------------------------------------------------------------------\n");
  while (aux) {
    printf("%-20s | %6d | %16p | %16p\n", aux->name, aux->count, aux, aux->prev);
    aux = aux->prev;
  }
  printf("\n");
}

/**
 * Função para imprimir as informações de um item de pilha.
 * @param item Ponteiro para o item de pilha.
 */
void print_item(TItemStack *item) {
  if (!item)
    return;
  printf("%-20s | %6d | %16p\n", item->name, item->count, item->prev);
}
