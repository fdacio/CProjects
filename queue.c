#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

void qstore(int n);
int qretrieve(void);
void print_queue(void);
void print_exception(void);
int validate_input(char *input);

int *boq, *p1, *retrived = NULL;
int *queue = NULL;

int errQueueOverflow = 0;
int errEmptyQueue = 0;
int errInvalidInput = 0;

void main(void) {

  char *p, input[10];

  /*stack aponta para o primeiro elemento da pilha*/
  queue = (int *)malloc(SIZE * sizeof(int));
  if (!queue) {
    printf("Erro ao alocar memória!\n");
    exit(1);
  }

  boq = queue; /* bos contem o inicio da pilha*/ 
  p1 = queue;  /* p1 aponta para o inicio da pilha */


  do {
    system("clear");
    printf("*** Fila de %d elementos: Enfileirar e Desenfileirar *** \n\n", SIZE);
    printf("( D )Retira um valor(Desenfileirar)\n");
    printf("( E )Sai do programa\n\n");

    print_exception();
    print_queue();

    printf("Digite um número: ");
    scanf("%s", input);

    errInvalidInput = validate_input(input);

    char *p;
    int value = strtol(input, &p, 10);

    if (value >= 0 && strlen(p) == 0) {
      qstore(value);
    }

    if (toupper(input[0]) == 'D') {
        printf("Retirado: %d->%p\n", qretrieve(), (p1));
        scanf("%s", input);
    }

  } while (toupper(input[0]) != 'E');

  printf("Fim do programa\n");
  free(queue);
}

void qstore(int n) {
  if (p1 == (boq + SIZE)) {
    errQueueOverflow = 1; // Estouro de fila
    return;
  }
  *p1 = n;
  p1++;
}

int qretrieve(void) {
  if (p1 == boq) {
    errEmptyQueue = 1; // Fila vazia
    return 0;
  }
  retrived = boq;
  boq++;
  return *retrived;
}

void print_queue(void) {
  
  printf("|%-2s|%-8s|%-20s|\n", "#", "Valor", "Ponteiro");
  printf("-----------------------------------\n");
  int *i;
  int idx = 0;
  for (i = boq; i < p1; i++) {
    printf("|%2d|%8d|%20p|\n", ++idx, *i, i);
  }
  printf("-----------------------------------\n");
  printf("p1->%p | boq->%p\n", p1, boq);
  printf("\n\n");
}

int validate_input(char *input) {
  char *p;
  strtol(input, &p, 10);
  if (strlen(p) != 0) {
    if (toupper(input[0]) != 'D' && toupper(input[0]) != 'E') {
      return 1; // Entrada inválida
    }
  }
  return 0; // Entrada válida
}

void print_exception(void) {
  if (errQueueOverflow) {
    printf("Estouro de Fila!\n\n");
    errQueueOverflow = 0;
  };
  if (errEmptyQueue) {
    printf("Fila vazia!\n\n");
    errEmptyQueue = 0;
  }
  if (errInvalidInput) {
    printf("Entrada inválida! %d\n\n", errInvalidInput);
    errInvalidInput = 0;
  }
}
