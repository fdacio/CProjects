#ifndef LIST_H
#define LIST_H

typedef struct club {
  int id;
  char nome[25];
  unsigned int pontos;
} TClub;

typedef struct item_list {
  TClub *data; 
  struct item_list *prev;
  struct item_list *next;
} TItemList;

void add_end_dup_linked(TItemList *new_item, TItemList **list);
void add_end_sing_linked(TItemList *new_item, TItemList **list);
void add_start_sing_linked(TItemList *new_item, TItemList **list);
void add_sorted_sing_linked(TItemList *new_item, TItemList **list);
void swap_item(TItemList *target, TItemList *source);
void sort_list_by_points(TItemList *list);
void sort_list_by_name(TItemList *list);
void bubble_sort_by_points(TItemList *list);
TItemList *find_item(const int id, TItemList *list);
TItemList *find_item_by_name(const char *nome, TItemList *list);
void remove_item_sing_linked(int id, TItemList **list);
void remove_item_dup_linked(TItemList *_remove, TItemList **list);
void free_list(TItemList **list);
TItemList *new_item_list(int _id, const char *nome, int pontos);
int get_next_id();

#endif