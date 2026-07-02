/* Testes para as funções de lista */
/*** Compile and build: gcc test.c src/list.c src/l_utils.c -Iinclude -o build/test  ****/
/*** Execute: ./build/test ****/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "l_utils.h"
#include "list.h"

// Macro auxiliar para exibir resultado
#define TEST(nome, condicao)                  \
     do                                       \
     {                                        \
          if (condicao)                       \
               printf("ok PASS: %s\n", nome); \
          else                                \
               printf("no FAIL: %s\n", nome); \
     } while (0)

void test_new_item()
{
     printf("\n--- new_item ---\n");

     TItemList *item = new_item_list(1, "Vasco da Gama", 10);

     TEST("id correto", item->data->id == 1);
     TEST("nome correto", strcmp(item->data->nome, "Vasco da Gama") == 0);
     TEST("pontos corretos", item->data->pontos == 10);
     TEST("next é NULL", item->next == NULL);
     TEST("prev é NULL", item->prev == NULL);

     free(item);
}

void test_add_end_sing_linked()
{
     printf("\n--- add_end_sing_linked ---\n");

     TItemList *list = NULL;
     TItemList *a = new_item_list(1, "Vasco da Gama", 10);
     TItemList *b = new_item_list(2, "Palmeiras", 20);
     TItemList *c = new_item_list(3, "Sao Paulo", 15);

     add_end_sing_linked(a, &list);
     TEST("primeiro elemento é Vasco da Gama",
          strcmp(list->data->nome, "Vasco da Gama") == 0);

     add_end_sing_linked(b, &list);
     TEST("segundo elemento é Palmeiras",
          strcmp(list->next->data->nome, "Palmeiras") == 0);

     add_end_sing_linked(c, &list);
     TEST("terceiro elemento é Sao Paulo",
          strcmp(list->next->next->data->nome, "Sao Paulo") == 0);
     TEST("terceiro next é NULL", list->next->next->next == NULL);

     print_list(list);

     free_list(&list);
}

void test_add_end_dup_linked()
{
     printf("\n--- add_end_dup_linked ---\n");

     TItemList *list = NULL;
     TItemList *a = new_item_list(1, "Vasco da Gama", 10);
     TItemList *b = new_item_list(2, "Palmeiras", 20);

     add_end_dup_linked(a, &list);
     add_end_dup_linked(b, &list);

     TEST("primeiro prev é NULL", list->prev == NULL);
     TEST("segundo prev aponta para primeiro", list->next->prev == list);
     TEST("segundo next é NULL", list->next->next == NULL);

     print_list_pointer(list);
     free_list(&list);
}

void test_add_start_sing_linked()
{
     printf("\n--- add_start_sing_linked ---\n");

     TItemList *list = NULL;
     TItemList *a = new_item_list(1, "Vasco da Gama", 10);
     TItemList *b = new_item_list(2, "Palmeiras", 20);

     add_start_sing_linked(a, &list);
     TEST("primeiro elemento é Vasco da Gama",
          strcmp(list->data->nome, "Vasco da Gama") == 0);

     add_start_sing_linked(b, &list);
     TEST("primeiro elemento agora é Palmeiras",
          strcmp(list->data->nome, "Palmeiras") == 0);
     TEST("segundo elemento é Vasco da Gama",
          strcmp(list->next->data->nome, "Vasco da Gama") == 0);
     TEST("segundo next é NULL", list->next->next == NULL);

     print_list_pointer(list);
     free_list(&list);
}

void test_add_start_dup_linked()
{
     printf("\n--- add_start_dup_linked ---\n");

     TItemList *list = NULL;
     TItemList *a = new_item_list(1, "Vasco da Gama", 10);
     TItemList *b = new_item_list(2, "Palmeiras", 20);

     add_start_dup_linked(a, &list);
     TEST("primeiro elemento é Vasco da Gama",
          strcmp(list->data->nome, "Vasco da Gama") == 0);

     add_start_dup_linked(b, &list);
     TEST("primeiro elemento agora é Palmeiras",
          strcmp(list->data->nome, "Palmeiras") == 0);
     TEST("segundo elemento é Vasco da Gama",
          strcmp(list->next->data->nome, "Vasco da Gama") == 0);
     TEST("segundo prev aponta para primeiro", list->next->prev == list);
     TEST("segundo next é NULL", list->next->next == NULL);

     print_list_pointer(list);
     free_list(&list);
}

void test_add_sorted_sing_linked()
{
     printf("\n--- add_sorted_sing_linked ---\n");

     TItemList *list = NULL;
     TItemList *a = new_item_list(1, "Vasco da Gama", 22);
     TItemList *b = new_item_list(2, "Palmeiras", 20);
     TItemList *c = new_item_list(3, "Sao Paulo", 15);
     TItemList *d = new_item_list(4, "Botafogo", 25);

     add_sorted_sing_linked(a, &list);
     add_sorted_sing_linked(b, &list);
     add_sorted_sing_linked(c, &list);
     add_sorted_sing_linked(d, &list);

     TEST("primeiro elemento é Botafogo",
          strcmp(list->data->nome, "Botafogo") == 0);
     TEST("segundo elemento é Vasco da Gama",
          strcmp(list->next->data->nome, "Vasco da Gama") == 0);
     TEST("terceiro elemento é Palmeiras",
          strcmp(list->next->next->data->nome, "Palmeiras") == 0);
     TEST("quarto elemento é Sao Paulo",
          strcmp(list->next->next->next->data->nome, "Sao Paulo") == 0);
     TEST("quarto next é NULL", list->next->next->next->next == NULL);

     print_list(list);
     free_list(&list);
}

void test_remove_item_sing_linked_meio_lista()
{
     printf("\n--- remove_item_sing_linked - meio da lista ---\n");

     TItemList *list = NULL;
     TItemList *item1 = new_item_list(1, "Vasco da Gama", 10);
     TItemList *item2 = new_item_list(2, "Palmeiras", 20);
     TItemList *item3 = new_item_list(3, "Sao Paulo", 15);
     add_end_sing_linked(item1, &list);
     add_end_sing_linked(item2, &list);
     add_end_sing_linked(item3, &list);

     // remove do meio
     remove_item_sing_linked(2, &list);
     TEST("Palmeiras removido", find_item(2, list) == NULL);
     TEST("Vasco da Gama ainda existe", find_item(1, list) != NULL);
     TEST("Sao Paulo ainda existe", find_item(3, list) != NULL);
     print_list_pointer(list);
     free_list(&list);
}

void test_remove_item_sing_linked_primeiro_elemento()
{
     printf("\n--- remove_item_sing_linked - primeiro elemento ---\n");

     TItemList *list = NULL;
     TItemList *item1 = new_item_list(1, "Vasco da Gama", 10);
     TItemList *item2 = new_item_list(2, "Palmeiras", 20);
     TItemList *item3 = new_item_list(3, "Sao Paulo", 15);
     add_end_sing_linked(item1, &list);
     add_end_sing_linked(item2, &list);
     add_end_sing_linked(item3, &list);

     // remove o primeiro
     remove_item_sing_linked(1, &list);
     TEST("Palmeiras é o novo primeiro", strcmp(list->data->nome, "Palmeiras") == 0);
     print_list_pointer(list);
     free_list(&list);
}

void test_remove_item_sing_linked_ultimo_elemento()
{
     printf("\n--- remove_item_sing_linked - Último elemento ---\n");

     TItemList *list = NULL;
     TItemList *item1 = new_item_list(1, "Vasco da Gama", 10);
     TItemList *item2 = new_item_list(2, "Palmeiras", 20);
     TItemList *item3 = new_item_list(3, "Sao Paulo", 15);
     TItemList *item4 = new_item_list(4, "Botafogo", 22);
     add_end_sing_linked(item1, &list);
     add_end_sing_linked(item2, &list);
     add_end_sing_linked(item3, &list);
     add_end_sing_linked(item4, &list);

     // remove o último
     remove_item_sing_linked(4, &list);
     TEST("São Paulo é o novo último", item3->next == NULL);
     print_list_pointer(list);
     free_list(&list);
}

void test_free_list()
{
     printf("\n--- free_list ---\n");

     // caso 1: lista com vários elementos
     TItemList *list = NULL;
     add_end_sing_linked(new_item_list(1, "Vasco da Gama", 10), &list);
     add_end_sing_linked(new_item_list(2, "Palmeiras", 20), &list);
     add_end_sing_linked(new_item_list(3, "Sao Paulo", 15), &list);
     free_list(&list);
     TEST("lista com 3 elementos liberada sem crash", 1); // se chegou aqui, não crashou
     print_list(list);

     // caso 2: lista com um elemento
     TItemList *list2 = NULL;
     add_end_sing_linked(new_item_list(1, "Vasco da Gama", 10), &list2);
     free_list(&list2);
     TEST("lista com 1 elemento liberada sem crash", 1);

     // caso 3: lista vazia (NULL)
     TItemList *list3 = NULL;
     free_list(&list3);
     TEST("lista NULL não causa crash", 1);
}

void test_find_item()
{
     printf("\n--- find_item ---\n");
     TItemList *list = NULL;
     add_end_sing_linked(new_item_list(1, "Vasco da Gama", 10), &list);
     add_end_sing_linked(new_item_list(2, "Palmeiras", 20), &list);
     add_end_sing_linked(new_item_list(3, "Sao Paulo", 15), &list);

     print_list(list);

     // caso 1 - procura por iteme de ID 1
     TItemList *item1 = find_item(1, list);
     TEST("Procura por ID 1 Vasco da Gama - Existe", item1->data->id == 1);

     // caso 2 - procura por iteme de ID 4 - não existe na lista
     TItemList *item2 = find_item(4, list);
     TEST("Procura por ID 4 - Não existe e retorna NULL", (item2 == NULL));

     TItemList *empty_list = NULL;
     TItemList *item3 = find_item(1, empty_list);
     TEST("Procura em uma lista vazia - Retorna NULL", (item3 == NULL));

     free_list(&list);
}

void test_find_by_name()
{
     printf("\n--- find_by_name ---\n");
     TItemList *list = NULL;
     add_end_sing_linked(new_item_list(1, "Vasco da Gama", 10), &list);
     add_end_sing_linked(new_item_list(2, "Palmeiras", 20), &list);
     add_end_sing_linked(new_item_list(3, "Sao Paulo", 15), &list);

     print_list(list);

     // caso 1 - procura por iteme de nome Vasco da Gama
     TItemList *item1 = find_item_by_name("Vasco da Gama", list);
     TEST("Procura por nome Vasco da Gama - Existe",
          strcmp(item1->data->nome, "Vasco da Gama") == 0);

     // caso 2 - procura por iteme por nome Flamengo - não existe na lista
     TItemList *item2 = find_item_by_name("Flamengo", list);
     TEST("Procura por nome Flamengo - Não existe e retorna NULL",
          (item2 == NULL));

     // caso 3 - procura por iteme por nome Sao Paulo - acentuação
     TItemList *item3 = find_item_by_name("Sao Paulo", list);
     TEST("Procura por nome Sao Paulo(acentuação) - Existe",
          strcmp(item3->data->nome, "Sao Paulo") == 0);

     TItemList *empty_list = NULL;
     TItemList *item4 = find_item_by_name("Vasco da Gama2", empty_list);
     TEST("Procura em uma lista vazia - Retorna NULL", (item4 == NULL));

     free_list(&list);
}

void test_swap_item()
{
     printf("\n--- swap_item ---\n");
     TItemList *list = NULL;
     add_end_sing_linked(new_item_list(1, "Vasco da Gama", 10), &list);
     add_end_sing_linked(new_item_list(2, "Palmeiras", 20), &list);
     add_end_sing_linked(new_item_list(3, "Sao Paulo", 15), &list);

     print_list(list);

     TItemList *item1 = find_item(1, list);
     TItemList *item2 = find_item(2, list);

     swap_item(item1, item2);

     TEST("Vasco da Gama agora tem ID de Palmeiras",
          item1->data->id == 2 && strcmp(item1->data->nome, "Palmeiras") == 0);
     TEST("Palmeiras agora tem ID de Vasco da Gama",
          item2->data->id == 1 && strcmp(item2->data->nome, "Vasco da Gama") == 0);

     print_list(list);
     free_list(&list);
}

void test_split_list()
{
     printf("\n--- split_list ---\n");
     TItemList *list = NULL;
     add_end_sing_linked(new_item_list(1, "Vasco da Gama", 26), &list);
     add_end_sing_linked(new_item_list(2, "Palmeiras", 20), &list);
     add_end_sing_linked(new_item_list(3, "Sao Paulo", 15), &list);
     add_end_sing_linked(new_item_list(4, "Botafogo", 25), &list);
     add_end_sing_linked(new_item_list(5, "Ceara", 24), &list);
     add_end_sing_linked(new_item_list(6, "Fortaleza", 12), &list);
     add_end_sing_linked(new_item_list(7, "Flamengo", 11), &list);
     add_end_sing_linked(new_item_list(8, "Fluminense", 15), &list);
     add_end_sing_linked(new_item_list(9, "Santos", 16), &list);
     add_end_sing_linked(new_item_list(10, "Corinthians", 11), &list);
     add_end_sing_linked(new_item_list(11, "Cruzeiro", 23), &list);
     add_end_sing_linked(new_item_list(12, "Coritiba", 18), &list);
     add_end_sing_linked(new_item_list(13, "Internacional", 19), &list);

     TItemList *left = NULL;
     TItemList *right = NULL;

     split_list(list, &left, &right);

     TEST("Left list head is Vasco da Gama",
          left != NULL && strcmp(left->data->nome, "Vasco da Gama") == 0);
     TEST("Right list head is Sao Paulo",
          right != NULL && strcmp(right->data->nome, "Sao Paulo") == 0);

     print_list(left);
     print_list(right);

     free_list(&left);
     free_list(&right);
}

int compare_name(TClub *a, TClub *b)
{
     return strcmp(a->nome, b->nome);
}

int compare_points(TClub *a, TClub *b)
{
     return b->pontos - a->pontos;
}

void test_merge_sort_by_name()
{
     printf("\n--- merge_sort_by_name ---\n");
     TItemList *list = NULL;
     add_end_sing_linked(new_item_list(1, "Vasco da Gama", 26), &list);
     add_end_sing_linked(new_item_list(2, "Palmeiras", 20), &list);
     add_end_sing_linked(new_item_list(3, "Sao Paulo", 15), &list);
     add_end_sing_linked(new_item_list(4, "Botafogo", 25), &list);
     add_end_sing_linked(new_item_list(5, "Ceara", 24), &list);
     add_end_sing_linked(new_item_list(6, "Fortaleza", 12), &list);
     add_end_sing_linked(new_item_list(7, "Flamengo", 11), &list);
     add_end_sing_linked(new_item_list(8, "Fluminense", 15), &list);
     add_end_sing_linked(new_item_list(9, "Santos", 16), &list);
     add_end_sing_linked(new_item_list(10, "Corinthians", 11), &list);
     add_end_sing_linked(new_item_list(11, "Cruzeiro", 23), &list);
     add_end_sing_linked(new_item_list(12, "Coritiba", 18), &list);
     add_end_sing_linked(new_item_list(13, "Internacional", 19), &list);

     merge_sort(&list, compare_name);

     TEST("First item is Botafogo",
          list != NULL && strcmp(list->data->nome, "Botafogo") == 0);
     TEST("Second item is Ceara",
          list->next != NULL && strcmp(list->next->data->nome, "Ceara") == 0);
     TEST("Third item is Corinthians",
          list->next->next != NULL &&
              strcmp(list->next->next->data->nome, "Corinthians") == 0);
     TEST("Fourth item is Coritiba",
          list->next->next->next != NULL &&
              strcmp(list->next->next->next->data->nome, "Coritiba") == 0);

     print_list(list);
     free_list(&list);
}

void test_merge_sort_by_points()
{
     printf("\n--- merge_sort_by_points ---\n");
     TItemList *list = NULL;
     add_end_dup_linked(new_item_list(1, "Vasco da Gama", 26), &list);
     add_end_dup_linked(new_item_list(2, "Palmeiras", 20), &list);
     add_end_dup_linked(new_item_list(3, "Sao Paulo", 15), &list);
     add_end_dup_linked(new_item_list(4, "Botafogo", 13), &list);
     add_end_dup_linked(new_item_list(5, "Ceara", 25), &list);
     add_end_dup_linked(new_item_list(6, "Fortaleza", 12), &list);
     add_end_dup_linked(new_item_list(7, "Flamengo", 11), &list);
     add_end_dup_linked(new_item_list(8, "Fluminense", 24), &list);
     add_end_dup_linked(new_item_list(9, "Santos", 16), &list);
     add_end_dup_linked(new_item_list(10, "Corinthians", 11), &list);
     add_end_dup_linked(new_item_list(11, "Cruzeiro", 23), &list);
     add_end_dup_linked(new_item_list(12, "Coritiba", 18), &list);
     add_end_dup_linked(new_item_list(13, "Internacional", 19), &list);

     merge_sort(&list, compare_points);

     TEST("First item is Vasco da Gama",
          list != NULL && strcmp(list->data->nome, "Vasco da Gama") == 0);
     TEST("Second item is Ceara",
          list->next != NULL && strcmp(list->next->data->nome, "Ceara") == 0);
     TEST("Third item is Fluminense",
          list->next->next != NULL &&
              strcmp(list->next->next->data->nome, "Fluminense") == 0);
     TEST("Fourth item is Cruzeiro",
          list->next->next->next != NULL &&
              strcmp(list->next->next->next->data->nome, "Cruzeiro") == 0);

     print_list(list);
     free_list(&list);
}

void test_merge_sort_empty_list()
{
     printf("\n--- merge_sort_empty_list ---\n");
     TItemList *list = NULL;

     merge_sort(&list, compare_name);

     TEST("Lista vazia permanece vazia", list == NULL);
     print_list(list);
}

void test_merge_sort_single_element()
{
     printf("\n--- merge_sort_single_element ---\n");
     TItemList *list = NULL;
     add_end_dup_linked(new_item_list(1, "Vasco da Gama", 26), &list);

     merge_sort(&list, compare_name);

     TEST("Lista com um elemento permanece inalterada",
          list != NULL && strcmp(list->data->nome, "Vasco da Gama") == 0 &&
              list->next == NULL);
     print_list(list);
     free_list(&list);
}

void test_merge_sort_two_elements()
{
     printf("\n--- merge_sort_two_elements ---\n");
     TItemList *list = NULL;
     add_end_dup_linked(new_item_list(1, "Palmeiras", 20), &list);
     add_end_dup_linked(new_item_list(2, "Vasco da Gama", 26), &list);

     merge_sort(&list, compare_name);

     TEST("Primeiro item é Palmeiras",
          list != NULL && strcmp(list->data->nome, "Palmeiras") == 0);
     TEST("Segundo item é Vasco da Gama",
          list->next != NULL && strcmp(list->next->data->nome, "Vasco da Gama") == 0);
     TEST("Segundo next é NULL", list->next->next == NULL);

     print_list(list);
     free_list(&list);
}

void test_merge_sort_identical_elements()
{
     printf("\n--- merge_sort_identical_elements ---\n");
     TItemList *list = NULL;
     add_end_dup_linked(new_item_list(1, "Vasco da Gama", 26), &list);
     add_end_dup_linked(new_item_list(2, "Vasco da Gama", 26), &list);
     add_end_dup_linked(new_item_list(3, "Vasco da Gama", 26), &list);

     merge_sort(&list, compare_name);

     TEST("Todos os elementos são Vasco da Gama",
          list != NULL && strcmp(list->data->nome, "Vasco da Gama") == 0 &&
              list->next != NULL &&
              strcmp(list->next->data->nome, "Vasco da Gama") == 0 &&
              list->next->next != NULL &&
              strcmp(list->next->next->data->nome, "Vasco da Gama") == 0 &&
              list->next->next->next == NULL);

     print_list(list);
     free_list(&list);
}

void test_merge_sort_already_sorted()
{
     printf("\n--- merge_sort_already_sorted ---\n");
     TItemList *list = NULL;
     add_end_dup_linked(new_item_list(1, "Botafogo", 13), &list);
     add_end_dup_linked(new_item_list(2, "Ceara", 25), &list);
     add_end_dup_linked(new_item_list(3, "Cruzeiro", 23), &list);
     add_end_dup_linked(new_item_list(4, "Fluminense", 24), &list);
     add_end_dup_linked(new_item_list(5, "Palmeiras", 20), &list);
     add_end_dup_linked(new_item_list(6, "Sao Paulo", 15), &list);
     add_end_dup_linked(new_item_list(7, "Vasco da Gama", 26), &list);

     merge_sort(&list, compare_points);

     TEST("Lista já ordenada por pontos permanece inalterada",
          list != NULL && strcmp(list->data->nome, "Vasco da Gama") == 0 &&
              list->next != NULL &&
              strcmp(list->next->data->nome, "Ceara") == 0 &&
              list->next->next != NULL &&
              strcmp(list->next->next->data->nome, "Fluminense") == 0 &&
              list->next->next->next != NULL &&
              strcmp(list->next->next->next->data->nome, "Cruzeiro") == 0 &&
              list->next->next->next->next != NULL &&
              strcmp(list->next->next->next->next->data->nome, "Palmeiras") ==
                  0 &&
              list->next->next->next->next->next != NULL &&
              strcmp(list->next->next->next->next->next->data->nome,
                     "Sao Paulo") == 0);
}

int main()
{
     printf("\n=============================\n");
     printf("TESTES - list.c");
     printf("\n=============================\n");

     //   test_new_item();
     //   test_add_end_sing_linked();
     //   test_add_end_dup_linked();
     //   test_add_start_sing_linked();
     //   test_add_start_dup_linked();
     //   test_add_sorted_sing_linked();
     //   test_find_item();
     //   test_find_by_name();
     //   test_swap_item();
     //   test_sort_list();
     //   test_remove_item_sing_linked_meio_lista();
     //   test_remove_item_sing_linked_primeiro_elemento();
     //   test_remove_item_sing_linked_ultimo_elemento();
     //   test_free_list();

     test_split_list();
     test_merge_sort_by_name();
     test_merge_sort_by_points();
     test_merge_sort_empty_list();
     test_merge_sort_single_element();
     test_merge_sort_two_elements();
     test_merge_sort_identical_elements();
     test_merge_sort_already_sorted();


     printf("\n=============================\n");
     printf("FIM DOS TESTES - list.c");
     printf("\n=============================\n\n");

     return 0;
}
