#include "valid_input.h"
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

unsigned int *stack, *pss, *tos, *dequeueValue;

int errStackOverflow = 0;
int errEmptyStack = 0;
int printPopValue = 0;

TValidateInput validInput;

/** Prototipos das Funções */
void push(unsigned int n);
unsigned int *pop(void);
void print_stack(void);
void print_stack_exception(void);
void print_validate_exception(void);
void print_pop(unsigned int *popValue);

int main(void) {

  char input[50];

  /*stack aponta para o primeiro elemento da pilha*/
  stack = (unsigned int *)malloc(SIZE * sizeof(unsigned int));
  if (!stack) {
    printf("Erro ao alocar memória!\n");
    return 1;
  }

  pss = stack;     /* pss = ponteiro para o início da pilha */
  tos = stack - 1; /* tos = ponteiro para o topo da pilha */

  while (1) {

    system("clear");
    printf("*** PILHA de %d elementos: Insert e Retrive *** \n", SIZE);
    printf("( P ) Retira um valor(Pop)\n");
    printf("( X ) Sair\n\n");

    print_stack_exception();
    print_validate_exception();
    print_pop(dequeueValue);
    print_stack();

    printf("Digite um número: ");
    scanf("%s", input);

    if (strlen(input) == 1) {
      char command = toupper(input[0]);
      if (command == 'P') {
        dequeueValue = pop();
        continue;
      }
      if (command == 'X') {
        break; // Sair do loop
      }
    }

    validInput = validate_input(input);
    if (validInput.isValid) {
      push(validInput.value);
    }
  }

  printf("Fim do programa\n");

  free(stack);

  return 0;
}

void push(unsigned int n) {
  if (tos - pss + 1 >= SIZE) {
    errStackOverflow = 1; // Estouro de pilha
    return;
  }
  tos++;
  *tos = n;
}

unsigned int *pop(void) {
  if (tos < pss) {
    errEmptyStack = 1; // Pilha vazia
    return 0;
  }
  unsigned int *value = tos; // Armazena o valor a ser retornado
  tos--;
  printPopValue = 1;
  return value;
}

void print_stack(void) {
  printf("tos->%p\n", tos);
  printf("pss->%p\n", pss);
  printf("|%-2s|%-10s|%-20s|\n", "#", "Valor", "Ponteiro");
  printf("-----------------------------------\n");
  unsigned int *i;
  unsigned int idx = (tos - pss) + 1; // Índice para exibição, começando do topo
  for (i = tos; i >= pss; i--) {
    printf("|%2d|%10u|%20p|\n", idx--, *i, i);
  }
  printf("\n\n");
}

void print_stack_exception(void) {
  if (errStackOverflow) {
    printf("Estouro de Pilha!\n\n");
    errStackOverflow = 0;
  };
  if (errEmptyStack) {
    printf("Pilha vazia!\n\n");
    errEmptyStack = 0;
  }
}

void print_pop(unsigned int *popValue) {
  if (printPopValue) { // Verifica se popValue é o valor que foi retirado
    printf("Retirado: %u->%p\n\n", *popValue, popValue);
	printPopValue = 0; // Reseta a flag para evitar mensagens repetidas
  }
}

void print_validate_exception(void) {
  if (validInput.isValid == 0 && validInput.message[0] != '\0') {
	printf("%s\n\n", validInput.message);
  }
}