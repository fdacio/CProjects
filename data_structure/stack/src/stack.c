#include "stack.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned int MAX = 4;

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

TItemStack *pop(TItemStack **topStack) {
  if (!(*topStack)) {
    return NULL;
  }
  TItemStack *i = *topStack;
  *topStack = i->prev;
  return i;
}

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