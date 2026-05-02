#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Campeonato {
  char nome[20];
  int ano;
  int qtdeTimes;
};

typedef struct time {
  char nome[20];
  int pontos;
  struct time *next;
} TClube;

TClube *lista = NULL;

void main() {

  int op;

  struct Campeonato camp1;
  strcpy(camp1.nome, "Brasileirão");
  camp1.ano = 2024;
  camp1.qtdeTimes = 0;

  do {
    
    TClube *novoTime = (TClube *)malloc(sizeof(TClube));
    printf("Informe o nome do time: ");
    scanf("%s", novoTime->nome);
    printf("Informe os pontos: ");
    scanf("%d", &novoTime->pontos);
    novoTime->next = NULL;

    camp1.qtdeTimes++;

    if (!lista) {
      printf("Primeiro Item");
      lista = novoTime;
    } else {

      lista->next = novoTime;
    }
    // lista = novoTime;

    TClube *aux = lista;
    while (aux) {
      printf("%s->%d Pontos\n", aux->nome, aux->pontos);
      aux = aux->next;
    }
    printf("0 - Sair | 1 - Continuar\n");
    scanf("%d", &op);

  } while (op != 0);

  printf("%s %d - %d times\n", camp1.nome, camp1.ano, camp1.qtdeTimes);

  printf("Tabela %p\n", lista);
  TClube *aux = lista;
  while (aux) {
    printf("%s->%d Pontos\n", aux->nome, aux->pontos);
    aux = aux->next;
  }
}
