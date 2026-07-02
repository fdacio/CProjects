#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "l_utils.h"

/**
 * Função para adicionar um item no final em uma lista singularmente encadeada
 * @param new_item Ponteiro para o item a ser adicionado
 * @param list Ponteiro para o ponteiro da lista (passagem por referência (**) para refletir modificação na variável global da lista)
 */
void add_end_sing_linked(TItemList *new_item, TItemList **list) {
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
  // nesse ponto, o ponteiro next do último item da lista aponta para o novo item
  item->next = new_item;
}

/**
 * Função para adicionar um item no final em uma lista duplamente encadeada
 * @param new_item Ponteiro para o item a ser adicionado
 * @param list Ponteiro para o ponteiro da lista (passagem por referência (**) para refletir modificação na variável global da lista)
 */
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

/**
 * Função para adicionar um item no inicio em uma lista singularmente encadeada
 * @param new_item Ponteiro para o item a ser adicionado
 * @param list Ponteiro para o ponteiro da lista (passagem por referência (**) para refletir modificação na variável global da lista)
 */
void add_start_sing_linked(TItemList *new_item, TItemList **list) {
  if (!*list) { // if the list is empty, add the first item and return
    *list = new_item;
    return;
  }
  // if the list is not empty, add the new item at the beginning
  new_item->next = *list;
  // update the list pointer to point to the new item
  *list = new_item;
}

/**
 * Função para adicionar um item no inicio em uma lista duplamente encadeada
 * @param new_item Ponteiro para o item a ser adicionado
 * @param list Ponteiro para o ponteiro da lista (passagem por referência (**) para refletir modificação na variável global da lista)
 */
void add_start_dup_linked(TItemList *new_item, TItemList **list) {
  if (!*list) { // if the list is empty, add the first item and return
    *list = new_item;
    return;
  }
  // if the list is not empty, add the new item at the beginning
  new_item->next = *list;
  (*list)->prev = new_item; // update the previous pointer of the old first item
  // update the list pointer to point to the new item
  *list = new_item;
}

/**
 * Função para adicionar um item ordenado em uma lista singularmente encadeada
 * @param new_item Ponteiro para o item a ser adicionado
 * @param list Ponteiro para o ponteiro da lista (passagem por referência (**) para refletir modificação na variável global da lista)
 */
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

/**
 * Função para trocar os dados de dois itens na lista singularmente/duplamente encadeada
 * A função troca apenas os ponteiros de dados (data) dos itens, mantendo a estrutura da lista inalterada.
 * @param _item1 Ponteiro para o item a ser trocado por _item2
 * @param _item2 Ponteiro para o item a ser trocado por _item1
 */
void swap_item(TItemList *_item1, TItemList *_item2) {
  // Salva ponteiros originais
  TItemList *item1_next = _item1->next;
  TItemList *item1_prev = _item1->prev;
  TItemList *item2_next = _item2->next;
  TItemList *item2_prev = _item2->prev;

  TItemList temp = *_item1;
  *_item1 = *_item2;
  *_item2 = temp;

  // Restaura os ponteiros — posição na lista não muda, só os dados
  _item1->next = item1_next;
  _item1->prev = item1_prev;
  _item2->next = item2_next;
  _item2->prev = item2_prev;
}

/**
 * Função de ordenação da lista de clubes por nome em ordem alfabética.
 * Função de ordenação simples, baseado no algoritmo de seleção.
 * A cada iteração, o item com menor nome é selecionado e colocado na posição correta.
 * @param list Ponteiro para a lista de clubes a ser ordenada.
 * @param compare Função de comparação para determinar a ordem dos elementos.
 */
void selection_sort(TItemList *list, int (*compare)(TClub *, TClub *)) {
  if (!list) {
    return;
  }
  TItemList *current = list;
  while (current) {
    TItemList *max_current = current;
    TItemList *next = current->next;
    while (next) {
      if (compare(next->data, max_current->data) < 0) {
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

/**
 * Função de ordenação da lista de clubes por nome em ordem alfabética.
 * Implementação com Bubble Sort (ordenação por troca).
 * A cada iteração, elementos adjacentes são comparados e trocados se necessário.
 * @param list Ponteiro para a lista de clubes a ser ordenada.
 * @param compare Função de comparação para determinar a ordem dos elementos.
 */
void bubble_sort(TItemList *list, int (*compare)(TClub *, TClub *)) {
  if (!list) {
    return;
  }
  
  TItemList *current = list;
  int swapped;
  
  // Loop externo: percorre toda a lista
  while (current) {
    swapped = 0;
    TItemList *next = list;
    
    // Loop interno: compara e troca elementos adjacentes
    while (next && next->next) {
      // Se o elemento atual é maior que o próximo, troca
      if (compare(next->data, next->next->data) > 0) {
        swap_item(next, next->next);
        swapped = 1;
      }
      next = next->next;
    }
    
    // Se não houve trocas, lista já está ordenada
    if (!swapped) {
      break;
    }
    current = current->next;
  }
}

/**
 * Função auxiliar para obter o item na posição idx da lista.
 * @param idx Índice do item a ser obtido (0-based).
 * @param list Ponteiro para a lista.
 * @return Ponteiro para o item na posição especificada ou NULL se não encontrado.
 */
TItemList *find_item_by_index(const int idx, TItemList *list) {
  TItemList *item = list;
  for (int i = 0; i < idx; i++) {
    item = item->next;
  }
  return item;
}

/**
 * Função de ordenação da lista de clubes por nome em ordem alfabética.
 * Implementação com Quick Sort (ordenação por partição).
 * A cada iteração, a lista é particionada em torno de um pivô, e os elementos são rearranjados.
 * @param list Ponteiro para a lista de clubes a ser ordenada.
 * @param low Índice do primeiro elemento da sublista a ser ordenada.
 * @param high Índice do último elemento da sublista a ser ordenada.
 * @param compare Função de comparação para determinar a ordem dos elementos.
 */
void quick_sort(TItemList *list, int low, int high, int (*compare)(TClub *, TClub *)) {

  register int i, j;
  TItemList *pivot, *i_pivot, *j_pivot;

  i = low;
  j = high;
  pivot = find_item_by_index((low+high)/2, list);
  i_pivot = find_item_by_index(i, list);
  j_pivot = find_item_by_index(j, list);

  do {
    while (compare(i_pivot->data, pivot->data) < 0 && (i < high)) {
      i++;
      i_pivot = find_item_by_index(i, list);
    }
    while (compare(j_pivot->data, pivot->data) > 0 && (j > low)) {
      j--;
      j_pivot = find_item_by_index(j, list);
    }
    if (i <= j) {
      swap_item(i_pivot, j_pivot);
      i++;
      j--;
    }
  } while (i <= j);
  
  if (low < j) {
    quick_sort(list, low, j, compare);
  }

  if (i < high) {
    quick_sort(list, i, high, compare);
  }

}

/**
 * Função auxiliar para mesclar duas listas ordenadas em uma única lista ordenada.
 * @param left Ponteiro para a primeira lista ordenada.
 * @param right Ponteiro para a segunda lista ordenada.
 * @param compare Função de comparação para determinar a ordem dos elementos.
 * @return Ponteiro para a lista mesclada e ordenada.
 */
TItemList *merge_lists(TItemList *left, TItemList *right, int (*compare)(TClub *, TClub *)) {
  if (!left) return right;
  if (!right) return left;

  TItemList *result = NULL;

  if (compare(left->data, right->data) <= 0) {
    result = left;
    result->next = merge_lists(left->next, right, compare);
  } else {
    result = right;
    result->next = merge_lists(left, right->next, compare);
  }

  return result;
}

/**
 * Função de ordenação da lista de clubes usando Merge Sort.
 * A cada iteração, a lista é dividida em duas metades, ordenadas recursivamente e mescladas.
 * @param list Ponteiro para o ponteiro da lista de clubes a ser ordenada (passagem por referência (**) para refletir modificação na variável global da lista)
 * @param compare Função de comparação para determinar a ordem dos elementos.
 */
void merge_sort(TItemList **list, int (*compare)(TClub *, TClub *)) {
  TItemList *head = *list;
  TItemList *left = NULL;
  TItemList *right = NULL;

  if(!head || !head->next) {
    return; // Base case: 0 or 1 element
  }

  split_list(head, &left, &right);

  merge_sort(&left, compare);
  merge_sort(&right, compare);

  *list = merge_lists(left, right, compare); // Update the original list pointer
}

/**
 * Função para encontrar um item na lista por ID.
 * @param id ID do item a ser encontrado.
 * @param list Ponteiro para a lista de clubes.
 * @return Ponteiro para o item encontrado ou NULL se não encontrado.
 */
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

/**
 * Função para encontrar um item na lista por nome.
 * @param nome Nome do item a ser encontrado.
 * @param list Ponteiro para a lista de clubes.
 * @return Ponteiro para o item encontrado ou NULL se não encontrado.
 */
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

/**
 * Função para remover um item de uma lista singularmente ligada.
 * @param id ID do item a ser removido.
 * @param list Ponteiro para o ponteiro da lista (passagem por referência (**))
 */
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

/**
 * Função para remover um item de uma lista duplamente ligada.
 * @param _remove Ponteiro para o item a ser removido.
 * @param list Ponteiro para o ponteiro da lista (passagem por referência (**)  
 */
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

/**
 * Função para liberar a memória alocada para uma lista de clubes.
 * @param list Ponteiro para o ponteiro da lista (passagem por referência (**) para refletir modificação na variável global da lista)
 */
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

/**
 * Função para gerar o próximo ID de clube.
 * @return O próximo ID de clube.
 */
int get_next_id() { 
  static int id = 0;
  return ++id; 
}

/**
 * Função para criar um novo item de lista com dados de clube.
 * @param _id ID do clube.
 * @param nome Nome do clube.
 * @param pontos Pontos do clube.
 * @return Ponteiro para o novo item de lista.  
 */
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

/**
 * Função para criar um novo descritor de lista.
 * @param list Ponteiro para a lista.
 * @return Ponteiro para o novo descritor de lista.
 */
TDescriptorList *create_descriptor_list(TItemList *list) {
  TDescriptorList *descriptor = (TDescriptorList *)malloc(sizeof(TDescriptorList));
  if (!descriptor) {
    perror("malloc failed");
    return NULL;
  }

  descriptor->first = list;
  descriptor->last = NULL;
  descriptor->size = 0;

  TItemList *current = list;
  while (current) {
    descriptor->last = current; // Atualiza o último item
    descriptor->size++;         // Incrementa o tamanho
    current = current->next;
  }

  return descriptor;
}
