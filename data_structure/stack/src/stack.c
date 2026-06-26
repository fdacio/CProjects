#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

const unsigned int MAX = 4;

/**
 * Função para adicionar um item ao topo da pilha.
 * @param new_item Ponteiro para o item a ser adicionado.
 * @param topStack Ponteiro para o ponteiro do topo da pilha (passagem por referência (**)).
 */
void push(TItemStack *new_item, TItemStack **topStack) {

  if (!(*topStack)) {
    new_item->count = 1;
    *topStack = new_item; // fist item
    return;
  }
  if (((*topStack)->count + 1) > MAX) {
    return; // stack overflow
  }

  new_item->count = (*topStack)->count + 1;
  new_item->prev = *topStack;
  *topStack = new_item;
}

/**
 * Função para remover o último item da pilha.
 * @param topStack Ponteiro para o ponteiro do topo da pilha (passagem por referência (**)).
 * @return Ponteiro para o item removido ou NULL se a pilha estiver vazia.
 */
TItemStack *pop(TItemStack **topStack) {
  if (!(*topStack)) {
    return NULL;
  }
  TItemStack *i = *topStack;
  *topStack = i->prev;
  return i;
}

/**
 * Função para criar um novo item de pilha.
 * @param name Nome do item.
 * @return Ponteiro para o novo item de pilha ou NULL em caso de falha.
 */
TItemStack *new_item_stack(const char *name) {

  TItemStack *new_item = (TItemStack *)malloc(sizeof(TItemStack));

  if (!new_item) {
    perror("malloc failed");
    return NULL;
  }

  strncpy(new_item->name, name, sizeof(new_item->name) - 1);
  new_item->name[sizeof(new_item->name) - 1] = '\0';
  new_item->prev = NULL;
  return new_item;
}

/**
 * Função para liberar a memória alocada para uma pilha.
 * @param topStack Ponteiro para o topo da pilha.
 */
void free_stack(TItemStack *topStack) {
  if (!topStack)
    return;
  TItemStack *aux = topStack;
  TItemStack *_free = NULL;
  while (aux) {
    _free = aux;
    aux = aux->prev;
    free(_free);
  }
}