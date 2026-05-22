#include "list.h"
#include <stdio.h>
#include <stdlib.h>

// Imprime uma tabela de itemes no console
void print_list(const TItemList *list) {
  if (!list) {
    return;
  }

  const TItemList *aux = list;

  printf("Pointer Table -> %p\n", (void *)aux);

  printf("|%-2s|%-4s|%-25s|%-10s|\n", "#", "ID", "Clube", "Pontos");
  printf("--------------------------------------------------------------\n");

  short int pos = 1;

  while (aux) {

    printf("|%2d|", pos++);

    printf("%4d|", aux->id);

    printf("%-25s|", aux->nome);

    printf("%10d|\n", aux->pontos);

    aux = aux->next;
  }
  printf("\n");
}

// Imprime uma tabela de ponteiros de itens no console
void print_list_pointer(const TItemList *list) {

  const TItemList *aux = list;

  printf("Pointer Table -> %p\n", (void *)aux);

  printf("|%-25s|%-15s|%-15s|%-15s|\n", "Clube", "Prev", "Current", "Next");
  for (int i = 0; i < 85; i++)
    printf("-");
  printf("\n");

  while (aux) {

    printf("|%-25s|", aux->nome);

    printf("%15p|", (void *)aux->prev);

    printf("%15p|", (void *)aux);

    printf("%15p|\n", (void *)aux->next);

    aux = aux->next;
  }
  printf("\n");
}

// Imprime uma nova lista classificada por pontos decrescente
// Isso para poder manter a orignal
void print_sorted_list(const TItemList *list) {
  if (!list) {
    return;
  }
  TItemList *sorted_list = NULL;
  const TItemList *aux = list;
  while (aux) {
    TItemList *new_item = new_item_list(aux->id, aux->nome, aux->pontos);
    add_sorted_sing_linked(new_item, &sorted_list);
    aux = aux->next;
  }
  print_list(sorted_list);
  free_list(sorted_list);
}

// Imprime um item no console
void print_item(const TItemList *item) {
  if (!item)
    return;
  printf("ID......: %d\n", item->id);
  printf("Nome....: %s\n", item->nome);
  printf("Pontos..: %d\n", item->pontos);
  printf("\n");
}

// Imprime os ponteiros do item no console
void print_item_pointer(const TItemList *item) {
  if (!item) {
    printf("nil");
    return;
  }
  printf("ID......: %d\n", item->id);
  printf("Prev....: %p\n", item->prev);
  printf("Next....: %p\n", item->next);
  printf("\n");
}
