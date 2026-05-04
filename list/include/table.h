#ifndef TABLE_H
#define TABLE_H

typedef struct club {
  int id;
  char nome[25];
  int pontos;
  struct club *prev;
  struct club *next;
} TClub;

void add_end_dup_linked(TClub *new_club, TClub **list);
void add_end_sing_linkend(TClub *new_club, TClub **list);
void add_start_sing_linkend(TClub *new_club, TClub **list);
void add_sorted_sing_linkend(TClub *new_club, TClub **list);
void swap_item(TClub *target, TClub *source);
void print_list(TClub *list);
void print_list_pointer(TClub *list);
void sort_list(TClub *list);
void print_sorted_list(TClub *list);
TClub *find_item(int id, TClub *list);
TClub *find_item_by_name(const char *nome, TClub *list);
void remove_item(int id, TClub **list);
void remove_item_dup_linked(TClub *_remove, TClub **list);
void print_item(TClub *club);
void print_item_pointer(TClub *club);
void free_list(TClub *list);
TClub *get_new_club(int _id, const char *nome, int pontos);
int get_next_id();

#endif