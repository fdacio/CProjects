#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termio.h>
#include <unistd.h>

void clear_screen(void);
void print_menu(void);
void add_club(void);

TClub *list = NULL;

int main(void) {

  char op;

  do {

    clear_screen();
    print_menu();

    scanf("%c", &op);
    getchar();

    if (op == '1') {
      add_club();
    }
    if (op == '2') {
      print_list(list);
      getchar();
    }
    if (op == '3') {
      print_sorted_list(list);
      getchar();
    }

  } while (op != '0');

  free_list(list);

  return 0;
}

void print_menu(void) {

  char menu[][30] = {
    "1 - Adicionar Club", 
    "2 - Exibir Tabela",
    "3 - Exibir Tabela Ordenada", 
    "0 - Sair"
  };

  char (*m)[30] = menu; // ponteiro para array de 20 chars
  char (*menu_end)[30] = menu + (sizeof(menu) / sizeof(menu[0]));

  while (m < menu_end) {
    printf("%s\n", *m);
    m++;
  }
  printf(">");
}

void add_club(void) {

  char nome[25];
  int pontos;

  printf("Informe o clube: ");

  fgets(nome, sizeof(nome), stdin);
  nome[strcspn(nome, "\n")] = '\0';

  printf("Informe os pontos: ");
  scanf("%d", &pontos);
  getchar();

  TClub *new_club = get_new_club(get_next_id(), nome, pontos);

  add_end(new_club, &list);
}

void clear_screen(void) {
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  printf("\033[H\033[J");
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
