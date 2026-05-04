#include "table.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_end(TClub *new_club, TClub **list) {
  if (!*list) {
    *list = new_club;
    return;
  }
  TClub *item = *list;
  while (item->next) {
    item = item->next;
  }
  item->next = new_club;
}

void add_end_dup_linked(TClub *new_club, TClub **list) {
  // se a lista estiver vazia, adiciona o primeiro e sai
  if (!*list) {
    *list = new_club;
    return;
  }
  // se a lista não estiver vazia, pecorre até o último
  TClub *item = *list;
  TClub *prev = NULL;
  while (item->next) {
    item = item->next;
  }
  // nesse ponto, o ponteiro de item, aponta para o ultimo elemento da lista
  // ness ponto, o ponteiro anterior do novo item aponto para o ultimo item da
  // lista

  new_club->prev = item;
  item->next = new_club;
}

void add_start(TClub *new_club, TClub **list) {
  if (!*list) {
    *list = new_club;
    return;
  }
  new_club->next = *list;
  *list = new_club;
}

void add_sorted(TClub *new_club, TClub **list) {
  TClub *p = *list;
  TClub *old = NULL;

  while (p && new_club->pontos <= p->pontos) {
    old = p;
    p = p->next;
  }

  if (old == NULL) {
    new_club->next = *list;
    *list = new_club;
  } else {
    new_club->next = p;
    old->next = new_club;
  }
}

void swap_item(TClub *_target, TClub *_source) {

  TClub temp = *_source;
  *_source = *_target;
  *_target = temp;

  TClub *tempNext = _target->next;
  _target->next = _source->next;
  _source->next = tempNext;
}

void sort_list(TClub *list) {
  if (!list) {
    return;
  }
  TClub *current = list;
  while (current) {
    TClub *max_current = current;
    TClub *next = current->next;

    while (next) {
      if (next->pontos > max_current->pontos) {
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

void print_list(TClub *list) {
  if (!list) {
    return;
  }

  TClub *aux = list;

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
}

void print_list_pointer(TClub *list) {
  if (!list) {
    return;
  }

  TClub *aux = list;

  printf("Pointer Table -> %p\n", (void *)aux);

  printf("|%-25s|%-15s|%-15s|%-15s|%-5s|\n", "Clube", "Prev", "Current", "Next",
         "Bytes");
  for (int i = 0; i < 90; i++)
    printf("-");
  printf("\n");

  while (aux) {

    printf("|%-25s|", aux->nome);

    printf("%15p|", (void *)aux->prev);

    printf("%15p|", (void *)aux);

    printf("%15p|", (void *)aux->next);

    uintptr_t diff = (aux->next) ? (uintptr_t)aux->next - (uintptr_t)aux : 0;

    printf("%15ld|\n", diff);

    aux = aux->next;
  }
}

void print_sorted_list(TClub *list) {
  if (!list) {
    return;
  }
  TClub *sorted_list = NULL;
  TClub *aux = list;
  while (aux) {
    TClub *new_club = get_new_club(aux->id, aux->nome, aux->pontos);
    add_sorted(new_club, &sorted_list);
    aux = aux->next;
  }
  print_list(sorted_list);
  free_list(sorted_list);
}

TClub *find_item(int id, TClub *list) {
  TClub *aux = list;
  while (aux) {
    if (aux->id == id) {
      return aux;
    }
    aux = aux->next;
  }
  return NULL;
}

TClub *find_item_by_name(char *nome, TClub *list) {
  TClub *aux = list;
  while (aux) {
    if (strcmp(aux->nome, nome) == 0) {
      return aux;
    }
    aux = aux->next;
  }
  return NULL;
}

void print_item(TClub *club) {
  if (!club)
    return;
  printf("ID......: %d\n", club->id);
  printf("Nome....: %s\n", club->nome);
  printf("Pontos..: %d\n", club->pontos);
}

void remove_item(int id, TClub **list) {
  if (!*list)
    return;
  TClub *_current = *list;
  TClub *_prev = NULL;
  while (_current) {
    if (_current->id == id) {
      // varifica se o item procurado é o primero da lista;
      //_prev ainda não aponta para nenhum item
      if (_prev == NULL) {
        // remover o primeiro
        *list = _current->next;
      } else {
        // nesse ponto o _prev já aponto para o item anterior ao encontro do id
        _prev->next = _current->next;
      }
      free(_current);
      return;
    }
    // Se o item atual(_current) não for o que está procurando, ele será o
    // anterior ao item prucrado
    _prev = _current;
    _current = _current->next;
  }
}

void remove_item_dup_linked(int id, TClub **list) {
  if (!*list)
    return;

  TClub *_remove = find_item(id, *list);
  if (!_remove)
    return;

  TClub *_prev = _remove->prev;
  TClub *_next = _remove->next;

  if (_prev == NULL) {
    *list = _next;
  } else {
    _prev->next = _next;
  }

  free(_remove);
}

void free_list(TClub *list) {
  if (!list)
    return;
  TClub *aux = list;
  TClub *_free = NULL;
  while (aux) {
    _free = aux;
    // printf("free->%p\n",_free);
    // printf("content before ->%s\n",_free->nome);
    free(_free);
    // printf("content after->%s\n",_free->nome);
    aux = aux->next;
  }
}

int get_next_id() { return ++id; }

TClub *get_new_club(int id, char *nome, int pontos) {
  TClub *new_club = (TClub *)malloc(sizeof(TClub));
  if (!new_club) {
    printf("Erro de memória");
    return NULL;
  }
  strcpy(new_club->nome, nome);
  new_club->pontos = pontos;
  new_club->next = NULL;
  new_club->prev = NULL;
  new_club->id = id;
  return new_club;
}