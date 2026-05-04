#include "table.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int id = 0;

// Função para adicionar um item no final em uma lista singularmente encadeada
// Parametro **list -> passagem por referencia, para refletir modificação na variável global da lista
void add_end_sing_linked(TClub *new_club, TClub **list) {
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
// Parametro **list -> passagem por referencia, para refletir modificação na variável global da lista
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
void add_start_sing_linked(TClub *new_club, TClub **list) {
  if (!*list) {
    *list = new_club;
    return;
  }
  new_club->next = *list;
  *list = new_club;
}

// Função para adicionar um item ordenado em uma lista singlamente encadeada
void add_sorted_sing_linked(TClub *new_club, TClub **list) {
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

// Função para troca de posição de dois itens na lista singlamente/duplamente
// encadeada
void swap_item(TClub *_target, TClub *_source) {
  // Salva ponteiros originais
  TClub *target_next = _target->next;
  TClub *target_prev = _target->prev;
  TClub *source_next = _source->next;
  TClub *source_prev = _source->prev;

  // Troca tudo via cópia de struct
  TClub temp = *_target;
  *_target = *_source;
  *_source = temp;

  // Restaura os ponteiros — posição na lista não muda, só os dados
  _target->next = target_next;
  _target->prev = target_prev;
  _source->next = source_next;
  _source->prev = source_prev;
}

// Ordena uma lista de clubes por pontos decrescente
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

// Imprime uma tabela de clubes no console
void print_list(const TClub *list) {
  if (!list) {
    return;
  }

  const TClub *aux = list;

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

// Imprime uma tabela de ponteiros de itens no console
void print_list_pointer(const TClub *list) {

  const TClub *aux = list;

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

// Imprime uma nova lista classificada por pontos decrescente
// Isso para poder manter a orignal
void print_sorted_list(const TClub *list) {
  if (!list) {
    return;
  }
  TClub *sorted_list = NULL;
  const TClub *aux = list;
  while (aux) {
    TClub *new_club = get_new_club(aux->id, aux->nome, aux->pontos);
    add_sorted_sing_linked(new_club, &sorted_list);
    aux = aux->next;
  }
  print_list(sorted_list);
  free_list(sorted_list);
}

// Retorna um ponteiro para o item encontado por ID
TClub *find_item(const int id, TClub *list) {
  TClub *aux = list;
  while (aux) {
    if (aux->id == id) {
      return aux;
    }
    aux = aux->next;
  }
  return NULL;
}

// Retorna um ponteiro para o item encontado por NOME
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

// Imprime um item no console
void print_item(const TClub *club) {
  if (!club)
    return;
  printf("ID......: %d\n", club->id);
  printf("Nome....: %s\n", club->nome);
  printf("Pontos..: %d\n", club->pontos);
}

// Imprime os ponteiros do item no console
void print_item_pointer(const TClub *club) {
  if (!club) {
    printf("nil");
    return;
  }
  printf("ID......: %d\n", club->id);
  printf("Prev....: %p\n", club->prev);
  printf("Next....: %p\n", club->next);
}

// remove um item de uma lista singularmente lincada
void remove_item_sing_linked(int id, TClub **list) {
  if (!*list)
    return;
  TClub *_current = *list;
  TClub *_prev = NULL;
  while (_current) {
    if (_current->id == id) {
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
void remove_item_dup_linked(TClub *_remove, TClub **list) {

  if (!*list)
    return;

  if (!_remove)
    return;

  TClub *_prev = _remove->prev;
  TClub *_next = _remove->next;

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

// Gera o próximo ID utilizando um variável estática global
int get_next_id() { return ++id; }

// Retorna um ponteiro para um item de lista alocado
TClub *get_new_club(int _id, const char *nome, int pontos) {
  TClub *new_club = (TClub *)malloc(sizeof(TClub));
  if (!new_club) {
    printf("Erro de alocação de memória");
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
