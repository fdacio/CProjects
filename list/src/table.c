#include "table.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int id = 0;

// Função para adicionar um item no final em uma lista singularmente encadeada
void add_end_sing_linkend(TClub *new_club, TClub **list) {
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

// Função para adicionar um item no final em uma lista duplamente encadeada
void add_end_dup_linked(TClub *new_club, TClub **list) {
  // se a lista estiver vazia, adiciona o primeiro e sai
  if (!*list) {
    *list = new_club;
    return;
  }
  // se a lista não estiver vazia, percorre até o último
  TClub *item = *list;
  while (item->next) {
    item = item->next;
  }

  // nesse ponto, o ponteiro de item, aponta para o ultimo elemento da lista
  // nesse ponto, o ponteiro anterior do novo item aponto para o ultimo item da
  // lista
  new_club->prev = item;
  item->next = new_club;
}

// Função para adicionar um item no inicio em uma lista singlamente encadeada
void add_start_sing_linkend(TClub *new_club, TClub **list) {
  if (!*list) {
    *list = new_club;
    return;
  }
  new_club->next = *list;
  *list = new_club;
}

// Função para adicionar um item ordenado em uma lista singlamente encadeada
void add_sorted_sing_linkend(TClub *new_club, TClub **list) {
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

// Função para troca de posição de dois itens na lista singlamente/duplamente encadeada
void swap_item(TClub *_target, TClub *_source) {
  // Salva ponteiros originais
  TClub *target_next = _target->next;
  TClub *target_prev = _target->prev;
  TClub *source_next = _source->next;
  TClub *source_prev = _source->prev;

  // Troca tudo via cópia de struct
  TClub temp = *_target;
  *_target  = *_source;
  *_source  = temp;

  // Restaura os ponteiros — posição na lista não muda, só os dados
  _target->next = target_next;
  _target->prev = target_prev;
  _source->next = source_next;
  _source->prev = source_prev;
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

  TClub *aux = list;

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
}

void print_sorted_list(TClub *list) {
  if (!list) {
    return;
  }
  TClub *sorted_list = NULL;
  TClub *aux = list;
  while (aux) {
    TClub *new_club = get_new_club(aux->id, aux->nome, aux->pontos);
    add_sorted_sing_linkend(new_club, &sorted_list);
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

TClub *find_item_by_name(const char *nome, TClub *list) {
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

void print_item_pointer(TClub *club) {
  if (!club) {
    printf("nil");
    return;
  }
  printf("ID......: %d\n", club->id);
  printf("Prev....: %p\n", club->prev);
  printf("Next....: %p\n", club->next);
}

void remove_item(int id, TClub **list) {
  if (!*list)
    return;
  TClub *_current = *list;
  TClub *_prev = NULL;
  while (_current) {
    if (_current->id == id) {
      // verifica se o item  é o primeiro da lista;
      //_prev ainda não aponta para nenhum item
      if (_prev == NULL) {
        // remover o primeiro
        *list = _current->next;
      } else {
        // nesse ponto o _prev já aponta para o item anterior ao encontro do id
        _prev->next = _current->next;
      }
      free(_current);
      return;
    }
    // Se o item atual(_current) não for o que está procurando, ele será o
    // anterior ao item procurado
    _prev = _current;
    _current = _current->next;
  }
}

void remove_item_dup_linked(TClub *_remove, TClub **list) {

  if (!*list)
    return;

  if (!_remove)
    return;

  TClub *_prev = _remove->prev;
  TClub *_next = _remove->next;

  // remove o primeiro
  if (_remove->prev == NULL) {
    *list = _remove->next;
    if (_next)
      _next->prev = NULL;
    free(_remove);
    return;
  }

  if (_next)
    _next->prev = _prev;
  if (_prev)
    _prev->next = _next;

  free(_remove);
}

void free_list(TClub *list) {
  if (!list)
    return;
  TClub *aux = list;
  TClub *_free = NULL;
  while (aux) {
    _free = aux;
    aux = aux->next;
    free(_free);
  }
}

//Gera o próximo ID utilizando um variável estática global
int get_next_id() { return ++id; }

TClub *get_new_club(int _id, const char *nome, int pontos) {
  TClub *new_club = (TClub *)malloc(sizeof(TClub));
  if (!new_club) {
    printf("Erro de memória");
    return NULL;
  }
  strncpy(new_club->nome, nome, sizeof(new_club->nome) - 1);
  new_club->nome[sizeof(new_club->nome) - 1] = '\0';
  new_club->pontos = pontos;
  new_club->next = NULL;
  new_club->prev = NULL;
  new_club->id = _id;
  return new_club;
}