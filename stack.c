#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

void push(int n);
int pop(void);
void print_stack(void);
void print_exception(void);
int validate_input(char *input);

int *tos, *p1, poped;
//int stack[SIZE];
int *stack = NULL;

int errStackOverflow = 0;
int errEmptyStack = 0;
int errInvalidInput = 0;

void main(void) {

  int value = 0;
  char *p =   NULL, input[10];
  int opc = 0;
  
  /*stack aponta para o primeiro elemento da pilha*/
  stack = (int *)malloc(SIZE * sizeof(int));
  if (!stack) {
    printf("Erro ao alocar memória!\n");
    exit(1);
  }

  tos = stack; /* tos contem o topo da pilha*/ 
  p1 = stack;  /* p1 aponta para o inicio da pilha */

  do {
  
    system("clear");
    printf("*** Pilha de %d elementos: Push e Pop *** \n", SIZE);
    printf("( D ) Retira um valor(Pop)\n");
    printf("( E ) Sair\n\n");

    print_exception();
    print_stack();
        
    printf("Digite um número: ");
    scanf("%s", input);
    
    errInvalidInput = validate_input(input);
    
    value = strtol(input, &p, 10);
    
    if (value >= 0 && strlen(p) == 0) {
      push(value);
    }

    if (toupper(input[0]) == 'D') {      
      printf("Retirado: %d->%p\n", pop(), (p1));
    }
       

  } while (toupper(input[0]) != 'E');

  printf("Fim do programa\n");
  
  free(stack);
}

void push(int n) {
  if (p1 == (tos + SIZE)) {
    errStackOverflow = 1; // Estouro de pilha
    return;
  }
  p1++;
  *p1 = n;
}

int pop(void) {
  if (p1 == tos) {
    errEmptyStack = 1; // Pilha vazia
    return 0;
  }
  p1--;
  return *(p1 + 1);
}

void print_stack(void) {
  printf("|%-2s|%-8s|%-20s|\n", "#", "Valor", "Ponteiro");
  printf("-----------------------------------\n");
  int *i;
  int idx = 0;
  for (i = p1; i > tos; i--) {
    printf("|%2d|%8d|%20p|\n", ++idx, *i, i);
  }
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
  if (errStackOverflow) {
    printf("Estouro de Pilha!\n\n");
    errStackOverflow = 0;
  };
  if (errEmptyStack) {
    printf("Pilha vazia!\n\n");
    errEmptyStack = 0;
  }
  if (errInvalidInput) {
    printf("Entrada inválida! %d\n\n", errInvalidInput);
    errInvalidInput = 0;
  }
}
// Função para converter caracteres para maiúsculas