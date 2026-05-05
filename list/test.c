#include "table.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macro auxiliar para exibir resultado
#define TEST(nome, condicao)                                                   \
  do {                                                                         \
    if (condicao)                                                              \
      printf("✅ PASSOU: %s\n", nome);                                         \
    else                                                                       \
      printf("❌ FALHOU: %s\n", nome);                                         \
  } while (0)

void test_get_new_club() {
  printf("\n--- get_new_club ---\n");

  TClub *club = get_new_club(1, "Vasco da Gama", 10);

  TEST("id correto", club->id == 1);
  TEST("nome correto", strcmp(club->nome, "Vasco da Gama") == 0);
  TEST("pontos corretos", club->pontos == 10);
  TEST("next é NULL", club->next == NULL);
  TEST("prev é NULL", club->prev == NULL);

  free(club);
}

void test_add_end_sing_linked() {
  printf("\n--- add_end_sing_linked ---\n");

  TClub *list = NULL;
  TClub *a = get_new_club(1, "Vasco da Gama", 10);
  TClub *b = get_new_club(2, "Palmeiras", 20);
  TClub *c = get_new_club(3, "São Paulo", 15);

  add_end_sing_linked(a, &list);
  TEST("primeiro elemento é Vasco da Gama",
       strcmp(list->nome, "Vasco da Gama") == 0);

  add_end_sing_linked(b, &list);
  TEST("segundo elemento é Palmeiras",
       strcmp(list->next->nome, "Palmeiras") == 0);

  add_end_sing_linked(c, &list);
  TEST("terceiro elemento é São Paulo",
       strcmp(list->next->next->nome, "São Paulo") == 0);
  TEST("terceiro next é NULL", list->next->next->next == NULL);

  free_list(list);
}

void test_add_end_dup_linked() {
  printf("\n--- add_end_dup_linked ---\n");

  TClub *list = NULL;
  TClub *a = get_new_club(1, "Vasco da Gama", 10);
  TClub *b = get_new_club(2, "Palmeiras", 20);

  add_end_dup_linked(a, &list);
  add_end_dup_linked(b, &list);

  TEST("primeiro prev é NULL", list->prev == NULL);
  TEST("segundo prev aponta para primeiro", list->next->prev == list);
  TEST("segundo next é NULL", list->next->next == NULL);

  free_list(list);
}

void test_remove_item_sing_linked() {
  printf("\n--- remove_item_sing_linked ---\n");

  TClub *list = NULL;
  add_end_sing_linked(get_new_club(1, "Vasco da Gama", 10), &list);
  add_end_sing_linked(get_new_club(2, "Palmeiras", 20), &list);
  add_end_sing_linked(get_new_club(3, "São Paulo", 15), &list);

  // remove do meio
  remove_item_sing_linked(2, &list);
  TEST("Palmeiras removido", find_item(2, list) == NULL);
  TEST("Vasco da Gama ainda existe", find_item(1, list) != NULL);
  TEST("São Paulo ainda existe", find_item(3, list) != NULL);

  // remove o primeiro
  remove_item_sing_linked(1, &list);
  TEST("novo primeiro é São Paulo", strcmp(list->nome, "São Paulo") == 0);

  // remove o último (lista fica vazia)
  remove_item_sing_linked(3, &list);
  TEST("lista vazia após remover todos", list == NULL);
}

void test_sort_list() {
  printf("\n--- sort_list ---\n");

  TClub *list = NULL;
  add_end_sing_linked(get_new_club(1, "Vasco da Gama", 10), &list);
  add_end_sing_linked(get_new_club(2, "Palmeiras", 30), &list);
  add_end_sing_linked(get_new_club(3, "São Paulo", 20), &list);

  sort_list(list);

  TEST("1º lugar: Palmeiras (30pts)", strcmp(list->nome, "Palmeiras") == 0);
  TEST("2º lugar: São Paulo (20pts)",
       strcmp(list->next->nome, "São Paulo") == 0);
  TEST("3º lugar: Vasco da Gama  (10pts)",
       strcmp(list->next->next->nome, "Vasco da Gama") == 0);

  free_list(list);
}

void test_free_list() {
  printf("\n--- free_list ---\n");

  // caso 1: lista com vários elementos
  TClub *list = NULL;
  add_end_sing_linked(get_new_club(1, "Vasco da Gama", 10), &list);
  add_end_sing_linked(get_new_club(2, "Palmeiras", 20), &list);
  add_end_sing_linked(get_new_club(3, "São Paulo", 15), &list);
  free_list(list);
  TEST("lista com 3 elementos liberada sem crash",
       1); // se chegou aqui, não crashou

  // caso 2: lista com um elemento
  TClub *list2 = NULL;
  add_end_sing_linked(get_new_club(1, "Vasco da Gama", 10), &list2);
  free_list(list2);
  TEST("lista com 1 elemento liberada sem crash", 1);

  // caso 3: lista vazia (NULL)
  TClub *list3 = NULL;
  free_list(list3);
  TEST("lista NULL não causa crash", 1);
}

void test_find_item() {
  printf("\n--- find_item ---\n");
  TClub *list = NULL;
  add_end_sing_linked(get_new_club(1, "Vasco da Gama", 10), &list);
  add_end_sing_linked(get_new_club(2, "Palmeiras", 20), &list);
  add_end_sing_linked(get_new_club(3, "São Paulo", 15), &list);

  printf("IDs na Lista:\n");
  TClub *aux = list;
  while (aux) {
    printf("%d\n", aux->id);
    aux = aux->next;
  }
  printf("\n");

  // caso 1 - procura por clube de ID 1
  TClub *club1 = find_item(1, list);
  TEST("Procura por ID 1 Vasco da Gama - Existe", club1->id == 1);

  // caso 2 - procura por clube de ID 4 - não existe na lista
  TClub *club2 = find_item(4, list);
  TEST("Procura por ID 4 - Não existe e retorna NULL", (club2 == NULL));

  TClub *empty_list = NULL;
  TClub *club3 = find_item(1, empty_list);
  TEST("Procura em uma lista vazia - Retorna NULL", (club3 == NULL));

  free_list(list);
}

void test_find_by_name() {
  printf("\n--- find_by_name ---\n");
  TClub *list = NULL;
  add_end_sing_linked(get_new_club(1, "Vasco da Gama", 10), &list);
  add_end_sing_linked(get_new_club(2, "Palmeiras", 20), &list);
  add_end_sing_linked(get_new_club(3, "São Paulo", 15), &list);

  printf("Nomes na Lista:\n");
  TClub *aux = list;
  while (aux) {
    printf("%s\n", aux->nome);
    aux = aux->next;
  }
  printf("\n");

  // caso 1 - procura por clube de nome Vasco da Gama
  TClub *club1 = find_item_by_name("Vasco da Gama", list);
  TEST("Procura por nome Vasco da Gama - Existe",
       strcmp(club1->nome, "Vasco da Gama") == 0);

  // caso 2 - procura por clube por nome Flamengo - não existe na lista
  TClub *club2 = find_item_by_name("Flamengo", list);
  TEST("Procura por nome Flamengo - Não existe e retorna NULL",
       (club2 == NULL));

  // caso 3 - procura por clube por nome São Paulo - acentuação
  TClub *club3 = find_item_by_name("São Paulo", list);
  TEST("Procura por nome São Paulo(acentuação) - Existe",
       strcmp(club3->nome, "São Paulo") == 0);

  TClub *empty_list = NULL;
  TClub *club4 = find_item_by_name("Vasco da Gama2", empty_list);
  TEST("Procura em uma lista vazia - Retorna NULL", (club4 == NULL));
  
  free_list(list);
}

int main() {
  printf("=============================\n");
  printf("     TESTES - table.c        \n");
  printf("=============================\n");

  test_get_new_club();
  test_add_end_sing_linked();
  test_add_end_dup_linked();
  test_find_item();
  test_find_by_name();
  test_remove_item_sing_linked();
  test_sort_list();
  test_free_list();

  printf("\n=============================\n");
  printf("        FIM DOS TESTES       \n");
  printf("=============================\n");

  return 0;
}