#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Função para imprimir no console os detalhes de uma lista de clubes.
 * @param list Ponteiro para a lista de clubes a ser impressa.
 */
void print_list(const TItemList *list) {
  if (!list) {
    return;
  }

  const TItemList *aux = list;

  printf("Pointer Table -> %p\n", (void *)aux);

  printf("|%-6s|%-6s|%-25s|%-8s|\n", "#", "ID", "Clube", "Pontos");
  for (int i = 0; i < 50; i++)
    printf("-");
  printf("\n");
  
  int pos = 1;

  while (aux) {

    printf("|%6d|", pos++);

    printf("%6d|", aux->data->id);

    printf("%-25s|", aux->data->nome);

    printf("%8d|\n", aux->data->pontos);

    aux = aux->next;
  }
  printf("\n");
}

/**
 * Função para imprimir no console os detalhes de uma lista de clubes.
 * @param list Ponteiro para a lista de clubes a ser impressa.
 */
void print_list_pointer(const TItemList *list) {

  const TItemList *aux = list;

  printf("Pointer Table -> %p\n", (void *)aux);

  printf("|%-25s|%-20s|%-20s|%-20s|\n", "Clube", "Prev", "Current", "Next");
  for (int i = 0; i < 90; i++)
    printf("-");
  printf("\n");

  while (aux) {

    printf("|%-25s|", aux->data->nome);

    printf("%20p|", (void *)aux->prev);

    printf("%20p|", (void *)aux);

    printf("%20p|\n", (void *)aux->next);

    aux = aux->next;
  }
  printf("\n");
}

/**
 * Função para imprimir no console os detalhes de uma lista de clubes até um limite especificado.
 * @param list Ponteiro para a lista de clubes a ser impressa.
 */
void print_head_list_pointer(const TItemList *list, int limit) {

  const TItemList *aux = list;

  printf("Pointer Table -> %p\n", (void *)aux);

  printf("|%-25s|%-20s|%-20s|%-20s|\n", "Clube", "Prev", "Current", "Next");
  for (int i = 0; i < 90; i++)
    printf("-");
  printf("\n");

  int count = 0;
  while (aux) {

    printf("|%-25s|", aux->data->nome);

    printf("%20p|", (void *)aux->prev);

    printf("%20p|", (void *)aux);

    printf("%20p|\n", (void *)aux->next);
  
    printf("\n");

    aux = aux->next;
    
    count++;
    if (count >= limit) {
      break;
    }
  }
}

/**
 * Função para imprimir uma nova lista ordenada por pontos decrescentes.
 * A lista original não é modificada.
 * @param list Ponteiro para a lista de clubes a ser ordenada e impressa.
 */
void print_sorted_list(const TItemList *list) {
  if (!list) {
    return;
  }
  TItemList *sorted_list = NULL;
  const TItemList *aux = list;
  while (aux) {
    TItemList *new_item = new_item_list(aux->data->id, aux->data->nome, aux->data->pontos);
    add_sorted_sing_linked(new_item, &sorted_list);
    aux = aux->next;
  }
  print_list(sorted_list);
  free_list(&sorted_list);
}

/**
 * Função para imprimir no console os detalhes de um item na lista.
 * @param item Ponteiro para o item a ser impresso.
 */
void print_item(const TItemList *item) {
  if (!item)
    return;
  printf("ID......: %d\n", item->data->id);
  printf("Nome....: %s\n", item->data->nome);
  printf("Pontos..: %d\n", item->data->pontos);
  printf("\n");
}

/**
 * Função para imprimir no console os ponteiros de um item na lista.
 * @param item Ponteiro para o item a ser impresso.
 */
void print_item_pointer(const TItemList *item) {
  if (!item) {
    printf("nil");
    return;
  }
  printf("ID......: %d\n", item->data->id);
  printf("Prev....: %p\n", item->prev);
  printf("Next....: %p\n", item->next);
  printf("\n");
}

/**
 * Função para imprimir no console os detalhes do descritor da lista.
 * @param descriptor Ponteiro para o descritor da lista.
 */
void print_descriptor(const TDescriptorList *descriptor) {
  if (!descriptor) {
    printf("Descriptor is NULL\n");
    return;
  }

  printf("Descriptor:\n");
  printf("First: %s\n", descriptor->first->data->nome);
  printf("Last:  %s\n", descriptor->last->data->nome);
  printf("Size:  %d\n", descriptor->size);
}

