#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned int MAX = 4;

/** Protótipos "private" funcões */
TItemQueue *cpy_first_item(TItemQueue *iniQueue);
void swap_item_queue(TItemQueue *_dest, TItemQueue *_src);

void enqueue(TItemQueue *new_item, TItemQueue **iniQueue,
             TItemQueue **endQueue) {

  if (!(*iniQueue)) {
    new_item->count = 1;
    *iniQueue = new_item;
    *endQueue = new_item;
    return;
  }

  if (((*endQueue)->count + 1) > MAX)
    return;

  new_item->count = (*endQueue)->count + 1;
  (*endQueue)->next = new_item;

  *endQueue = new_item;
}

TItemQueue *dequeue(TItemQueue **iniQueue, TItemQueue **endQueue) {

  if (!(*iniQueue))
    return NULL;

  TItemQueue *removed = cpy_first_item(*iniQueue);

  TItemQueue *current = *iniQueue;

  // desloca os dados dos próximos nós
  while (current->next) {

    // troca o valores do atual com o proximo do atual
    swap_item_queue(current, current->next);

    // se o próximo for o último
    if (current->next->next == NULL) {

      TItemQueue *last = current->next;

      current->next = NULL;
      *endQueue = current;

      free(last);

      return removed;
    }

    current = current->next;
  }

  // caso exista apenas um elemento
  free(*iniQueue);

  *iniQueue = NULL;
  *endQueue = NULL;

  return removed;
}

TItemQueue *new_item_queue(const char *name) {

  TItemQueue *new_item = (TItemQueue *)malloc(sizeof(TItemQueue));

  if (!new_item) {
    perror("malloc failed");
    return NULL;
  }

  strncpy(new_item->name, name, sizeof(new_item->name) - 1);
  new_item->name[sizeof(new_item->name) - 1] = '\0';
  new_item->next = NULL;
  return new_item;
}

void free_queue(TItemQueue *iniQueue) {
  if (!iniQueue)
    return;

  TItemQueue *current = iniQueue;
  TItemQueue *_free = NULL;
  while (current) {
    _free = current;
    current = current->next;
    free(_free);
  }
}

TItemQueue *cpy_first_item(TItemQueue *iniQueue) {

  //  TItemQueue *first_item = iniQueue;

  TItemQueue *first_item = malloc(sizeof(TItemQueue));

  if (!first_item)
    return NULL;

  // salva os dados do primeiro elemento
  memcpy(first_item, iniQueue, sizeof(TItemQueue));
  first_item->next = NULL;

  return first_item;
}

void swap_item_queue(TItemQueue *_dest, TItemQueue *_src) {

  char *_name = _src->name;
  unsigned int _count = _src->count - 1;

  strncpy(_dest->name, _name, sizeof(_dest->name) - 1);
  _dest->name[sizeof(_dest->name) - 1] = '\0';
  _dest->count = _count;
}
