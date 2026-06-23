#include "list.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int id = 0;

// Função para adicionar um item no final em uma lista singularmente encadeada
// Parametro **list -> passagem por referencia, para refletir modificação na variável global da lista
void add_end_sing_linked(TItemList *new_item, TItemList **list) {
  if (!*list) {
    *list = new_item;
    return;
  }
  TItemList *item = *list;
  while (item->next) {
    item = item->next;
  }
  item->next = new_item;
}

// Função para adicionar um item no final em uma lista duplamente encadeada
// Parametro **list -> passagem por referencia, para refletir modificação na variável global da lista
void add_end_dup_linked(TItemList *new_item, TItemList **list) {
  // se a lista estiver vazia, adiciona o primeiro e sai
  if (!*list) {
    *list = new_item;
    return;
  }
  // se a lista não estiver vazia, percorre até o último
  TItemList *item = *list;
  while (item->next) {
    item = item->next;
  }

  // nesse ponto, o ponteiro anterior do novo item aponto para o ultimo item da lista
  new_item->prev = item;
  // nesse ponto, o ultimo elemento da lista aponta para o novo elemento
  item->next = new_item;
}

// Função para adicionar um item no inicio em uma lista singlamente encadeada
void add_start_sing_linked(TItemList *new_item, TItemList **list) {
  if (!*list) {
    *list = new_item;
    return;
  }
  new_item->next = *list;
  *list = new_item;
}

// Função para adicionar um item ordenado em uma lista singlamente encadeada
void add_sorted_sing_linked(TItemList *new_item, TItemList **list) {
  TItemList *p = *list;
  TItemList *old = NULL;

  while (p && new_item->data->pontos <= p->data->pontos) {
    old = p;
    p = p->next;
  }

  if (old == NULL) {
    new_item->next = *list;
    *list = new_item;
  } else {
    new_item->next = p;
    old->next = new_item;
  }
}

// Função para troca de posição de dois itens na lista singlamente/duplamente
// encadeada
void swap_item(TItemList *_target, TItemList *_source) {
  // Salva ponteiros originais
  TItemList *target_next = _target->next;
  TItemList *target_prev = _target->prev;
  TItemList *source_next = _source->next;
  TItemList *source_prev = _source->prev;

  // Troca tudo via cópia de struct
  TItemList temp = *_target;
  *_target = *_source;
  *_source = temp;

  // Restaura os ponteiros — posição na lista não muda, só os dados
  _target->next = target_next;
  _target->prev = target_prev;
  _source->next = source_next;
  _source->prev = source_prev;
}

/**
 * Método de ordenação da lista de clubes por pontos decrescente.
 * Método de ordenação simples, baseado no algoritmo de seleção.
 * A cada iteração, o item com maior pontuação é selecionado e colocado na posição correta.
 * @param list Ponteiro para a lista de clubes a ser ordenada.
 */
void sort_list(TItemList *list) {
  if (!list) {
    return;
  }
  TItemList *current = list;
  while (current) {
    TItemList *max_current = current;
    TItemList *next = current->next;

    while (next) {
      if (next->data->pontos > max_current->data->pontos) {
        max_current = next;
      }
      next = next->next;
    }

    if (max_current != current) {
      swap_item(current, max_current);
    }

    current = current->next;
  }
}

// Retorna um ponteiro para o item encontado por ID
TItemList *find_item(const int id, TItemList *list) {
  TItemList *aux = list;
  while (aux) {
    if (aux->data->id == id) {
      return aux;
    }
    aux = aux->next;
  }
  return NULL;
}

// Retorna um ponteiro para o item encontado por NOME
TItemList *find_item_by_name(const char *nome, TItemList *list) {
  TItemList *aux = list;
  while (aux) {
    if (strcmp(aux->data->nome, nome) == 0) {
      return aux;
    }
    aux = aux->next;
  }
  return NULL;
}

// remove um item de uma lista singularmente lincada
void remove_item_sing_linked(int id, TItemList **list) {
  
  if (!*list)
    return;

  TItemList *_current = *list;
  TItemList *_prev = NULL;
  while (_current) {
    if (_current->data->id == id) {
      // Nesse ponto o item a ser removido para a ser o _current
      //  verifica se o item  é o primeiro da lista;
      //_prev ainda não aponta para nenhum item
      if (_prev == NULL) {
        // o primeiro item da lista passa o próximo do item item a ser removido
        *list = _current->next;
      } else {
        // nesse ponto o _prev já aponta para o item anterior do item a ser
        // removido então o proximo do item anteriar ao do ser removido,
        // apontará para do item a ser removido
        _prev->next = _current->next;
      }
      // libera a memoria do item a ser removido
      free(_current);
      return;
    }
    // Se o item atual(_current) não for o que está procurando, ele será o
    // anterior ao item procurado
    _prev = _current;
    _current = _current->next;
  }
}

// remove um item de uma lista duplamente lincada
void remove_item_dup_linked(TItemList *_remove, TItemList **list) {

  if (!*list)
    return;

  if (!_remove)
    return;

  TItemList *_prev = _remove->prev;
  TItemList *_next = _remove->next;

  // Verfica se o item a removido é o primeiro
  if (_prev == NULL) {
    // Lista aponta para o próximo item do item a ser removido,
    // ou seja, aponta para o novo primerio item da lista
    *list = _next;
    // Verfica se item a ser removido tem um próximo,
    // ou seja, se ele é o primeiro e não é o único.
    // O próximo o item a ser removido passa a ser o primeiro,
    // então o anterior (prev) passar a apontar para NULL
    if (_next)
      _next->prev = NULL;
    free(_remove);
    return;
  }

  // Aqui o item a ser removido é qualquer item que não é o primeiro,
  // ou seja, do segundo em diante

  // Verifica se o item a ser removido tem um anterior,
  // ou seja, o item a ser removido não é o primeiro
  if (_prev)
    _prev->next =
        _next; // Nessa atribuilção, se o item a ser removido é o ultimo, _next
               // é NULL e o item anterior passa a ser o último

  // Verifica se o item a ser removido tem um próximo,
  // ou seja, ele não é o ultimo
  if (_next)
    _next->prev = _prev;

  // Libera a memória do item removido
  free(_remove);
}

// Liebra as memórias dos itens da lista
void free_list(TItemList **list) {
  if (!list)
    return;
  TItemList *aux = *list;
  TItemList *_free = NULL;
  while (aux) {
    _free = aux;
    aux = aux->next;
    free(_free->data); // libera a memória do clube
    free(_free);
  }
  *list = NULL; // opcional: define a lista como NULL após liberar
}

// Gera o próximo ID utilizando um variável estática global
int get_next_id() { return ++id; }

// Retorna um ponteiro para um item de lista alocado
TItemList *new_item_list(int _id, const char *nome, int pontos) {
  
  TItemList *new_item = (TItemList *)malloc(sizeof(TItemList));
  TClub *new_club = (TClub *)malloc(sizeof(TClub));

  if (!new_club) {
    perror("malloc failed");
    return NULL; 
  } 
  
  if (!new_item) {
    perror("malloc failed");
    return NULL;
  }

  new_club->id = _id;
  strncpy(new_club->nome, nome, sizeof(new_club->nome) - 1);
  new_club->nome[sizeof(new_club->nome) - 1] = '\0';
  new_club->pontos = pontos;

  new_item->data = new_club;
  new_item->next = NULL;
  new_item->prev = NULL;
  return new_item;

}
