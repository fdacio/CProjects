#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "valid_input.h"

#define SIZE 10

unsigned int *tos, *p1;
unsigned int *stack = NULL;

int errStackOverflow = 0;
int errEmptyStack = 0;
TValidateInputReturn validInput;
int printPop = 0;

/** Prototipos das Funções */
void push(unsigned int n);
unsigned int pop(void);
void print_stack(void);
void print_exception(void);
void print_pop(unsigned int popValue);
TValidateInputReturn validate_input(const char *input);

int main(void) {

  unsigned int value = 0;
  char *p = NULL, input[50];
  int opc = 0;
  unsigned int popValue = 0;

  /*stack aponta para o primeiro elemento da pilha*/
  stack = (unsigned int *)malloc(SIZE * sizeof(unsigned int));
  if (!stack) {
    printf("Erro ao alocar memória!\n");
    return 1;
  }

  tos = stack;    /* tos aponta para o início da pilha */
  p1 = stack - 1; /* p1 aponta para o topo da pilha (vazia: antes do início) */

  do {

    system("clear");
    printf("*** Pilha de %d elementos: Push e Pop *** \n", SIZE);
    printf("( D ) Retira um valor(Pop)\n");
    printf("( E ) Sair\n\n");

    print_exception();
    print_pop(popValue);
    print_stack();

    printf("Digite um número: ");
    scanf("%s", input);

    if (toupper(input[0]) == 'D') {
        popValue = pop();
        printPop = 1;
        continue;
    }

    validInput = validate_input(input);

    if (validInput.value != NULL) {

      push(*validInput.value);

    }

  } while (toupper(input[0]) != 'E');

  printf("Fim do programa\n");

  free(stack);

  return 0;
}

void push(unsigned int n) {
  if (p1 - tos + 1 >= SIZE) {
    errStackOverflow = 1; // Estouro de pilha
    return;
  }
  p1++;
  *p1 = n;
}

unsigned int pop(void) {
  if (p1 < tos) {
    errEmptyStack = 1; // Pilha vazia
    return 0;
  }
  unsigned int val = *p1;
  p1--;
  return val;
}

void print_stack(void) {
  printf("|%-2s|%-10s|%-20s|\n", "#", "Valor", "Ponteiro");
  printf("-----------------------------------\n");
  unsigned int *i;
  int idx = 0;
  for (i = p1; i >= tos; i--) {
    printf("|%2d|%10u|%20p|\n", ++idx, *i, i);
  }
  printf("\n\n");
}

void print_exception(void) {
  if (errStackOverflow) {
    printf("Estouro de Pilha!\n\n");
    errStackOverflow = 0;
  };
  if (errEmptyStack) {
    printf("Pilha vazia!\n\n");
    errEmptyStack = 0;
    printPop = 0;
  }
  if (validInput.value == NULL) {
    printf("%s!\n\n", validInput.message);
  }
}

void print_pop(unsigned int popValue) {
  if (printPop) {
    printf("Retirado: %u->%p\n\n", popValue, (p1 + 1));
    printPop = 0;
  }
}

