#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

const unsigned int MAX = 4;

/** Protótipos "private" funcões */
TItemQueue *cpy_first_item(TItemQueue *iniQueue);
void swap_item_queue(TItemQueue *_dest, TItemQueue *_src);

/**
 * Função para adicionar um item ao final da fila.
 * @param new_item Ponteiro para o item a ser adicionado.
 * @param iniQueue Ponteiro para o ponteiro do início da fila (passagem por referência (**)).
 * @param endQueue Ponteiro para o ponteiro do final da fila (passagem por referência (**)).
 */
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

/**
 * Função para remover o primeiro item da fila.
 * @param iniQueue Ponteiro para o ponteiro do início da fila (passagem por referência (**)).
 * @param endQueue Ponteiro para o ponteiro do final da fila (passagem por referência (**)).
 * @return Ponteiro para o item removido ou NULL se a fila estiver vazia. 
 */
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

/**
 * Função para criar um novo item de fila.
 * @param name Nome do item.
 * @return Ponteiro para o novo item de fila ou NULL em caso de falha.
 */
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

/**
 * Função para liberar a memória alocada para uma fila.
 * @param iniQueue Ponteiro para o início da fila.
 */
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

/**
 * Função para copiar o primeiro item de uma fila.
 * @param iniQueue Ponteiro para o início da fila.
 * @return Ponteiro para o novo item copiado ou NULL em caso de falha.
 */
TItemQueue *cpy_first_item(TItemQueue *iniQueue) {

  TItemQueue *first_item = malloc(sizeof(TItemQueue));

  if (!first_item)
    return NULL;

  // salva os dados do primeiro elemento
  memcpy(first_item, iniQueue, sizeof(TItemQueue));
  first_item->next = NULL;

  return first_item;
}

/**
 * Função para trocar os dados de dois itens na fila
 * @param _dest Ponteiro para o item de destino.
 * @param _src Ponteiro para o item de origem.
 */
void swap_item_queue(TItemQueue *_dest, TItemQueue *_src) {

  char *_name = _src->name;
  unsigned int _count = _src->count - 1;

  strncpy(_dest->name, _name, sizeof(_dest->name) - 1);
  _dest->name[sizeof(_dest->name) - 1] = '\0';
  _dest->count = _count;
}
