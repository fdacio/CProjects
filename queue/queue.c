#include "valid_input.h"
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 10;

unsigned int *queue, *peq, *soq;
unsigned int dequeueValue;

int errQueueOverflow = 0;
int errEmptyQueue = 0;
int printDequeueValue = 0;

/** Prototipos das Funções */
void enqueue(unsigned int n);
unsigned int dequeue(void);
void print_queue(void);
void print_queue_exception(void);
void print_validate_exception(TValidateInput validInput);
void print_dequeue(unsigned int popValue);

int main(void) {

  /*queue aponta para o primeiro elemento da pilha*/
  queue = (unsigned int *)malloc(SIZE * sizeof(unsigned int));
  if (!queue) {
    printf("Erro ao alocar memória!\n");
    return 1;
  }

  peq = queue; /* peq = ponteiro para o fim da FILA vazia*/
  soq = queue; /* soq = ponteiro para o inicio da FILA */

  TValidateInput validInput = {.message = "", .isValid = 0, .value = 0};
  char input[50];

  while (1) {

    system("clear");
    printf("*** FILA de %d elementos: Enqueue e Dequeue *** \n", SIZE);
    printf("( D ) Retira um valor(Dequeue)\n");
    printf("( X ) Sair\n\n");

    print_queue_exception();
    print_validate_exception(validInput);
    print_dequeue(dequeueValue);
    print_queue();

    printf("Digite um número: ");
    scanf("%49s", input);

    if (strlen(input) == 1) {
      char command = toupper(input[0]);
      if (command == 'D') {
        dequeueValue = dequeue();
        continue;
      }
      if (command == 'X') {
        break; // Sair do loop
      }
    }

    validInput = validate_input(input);
    if (validInput.isValid) {
      enqueue(validInput.value);
    }
  }

  printf("Fim do programa\n");

  free(queue);

  return 0;
}

void enqueue(unsigned int n) {
  if (peq == queue + SIZE) {	
    if (soq > queue) {
      int elementos = peq - soq;
      memmove(queue, soq, elementos * sizeof(unsigned int));
      soq = queue;
      peq = queue + elementos;
    } else {
      errQueueOverflow = 1;
      return;
    }
  }
  *peq = n;
  peq++;
}

unsigned int dequeue(void) {
  if (peq == soq) {
    errEmptyQueue = 1; // Fila vazia
    return 0;
  }
  unsigned int value = *soq; // Armazena o valor a ser retornado
  soq++;
  printDequeueValue = 1;
  /* Reset quando esvaziar */
  if (soq == peq) {
    soq = queue;
    peq = queue;
  }
  return value;
}

void print_queue(void) {
  printf("soq->%p\n", soq);
  printf("peq->%p\n", peq);
  printf("|%-2s|%-10s|%-20s|\n", "#", "Valor", "Ponteiro");
  printf("-----------------------------------\n");
  unsigned int *i;
  unsigned int idx = 1; // Índice para exibição, começando do topo
  for (i = soq; i < peq; i++) {
    printf("|%2d|%10u|%20p|\n", idx++, *i, i);
  }
  printf("\n\n");
}

void print_queue_exception(void) {
  if (errQueueOverflow) {
    printf("Estouro da Fila!\n\n");
    errQueueOverflow = 0;
  }
  if (errEmptyQueue) {
    printf("Fila vazia!\n\n");
    errEmptyQueue = 0;
  }
}

void print_dequeue(const unsigned int dequeueValue) {
  if (printDequeueValue) { // Verifica se a fila não está vazia
    printf("Retirado: %u->%p\n\n", dequeueValue, soq - 1);
    printDequeueValue =
        0; // Reseta a flag para não imprimir novamente até a próxima retirada
  }
}

void print_validate_exception(TValidateInput validInput) {
  if (!validInput.isValid && validInput.message[0] != '\0') {
    printf("%s\n\n", validInput.message);
  }
}