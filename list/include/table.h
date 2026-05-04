#ifndef TABLE_H
#define TABLE_H

volatile static int id = 0;
typedef struct club {
  int id;
  char nome[25];
  int pontos;
  struct club *prev;
  struct club *next;
} TClub;
void add_end_dup_linked(TClub *new_club, TClub **list);
void add_end(TClub *new_club, TClub **list);
void add_start(TClub *new_club, TClub **list);
void add_sorted(TClub *new_club, TClub **list);
void swap_item(TClub *target, TClub *source);
void print_list(TClub *list);
void print_list_pointer(TClub *list);
void sort_list(TClub *list);
void print_sorted_list(TClub *list);
TClub *find_item(int id, TClub *list);
void remove_item(int id, TClub **list);
void remove_item_dup_linked(int id, TClub **list);
void print_item(TClub *club);
void free_list(TClub *list);
TClub *get_new_club(int id, char *nome, int pontos);
int get_next_id();

#endif