#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int TFuncao(int x, int y);
TFuncao *operacao;

typedef char *TFuncao1P(int x);
TFuncao1P *operacao1P;

int adicao(int x, int y);
int subtracao(int x, int y);
int mutiplicacao(int x, int y);
int divisao(int x, int y);
int executa(int x, int y, TFuncao *operacao);
char *executa1P(int x, TFuncao1P *operacao);
char *parImpar(int x);

int main() {

  int n1, n2;
  int opc;

  do {
    system("clear");
    printf("(1) - Adição | (2) - Subtração | (3) - Multiplicação | (4) - Divisão | (5) - Par ou Impar | (0) - Sair \n");
    printf("Informe a operação: ");
    
    if (scanf("%d", &opc) != 1) {
      printf("Error: Entrada inválida.\n");
      while (getchar() != '\n'); // Limpa o buffer de entrada
      continue;
    }

    switch (opc) {
    case 1:
      operacao = adicao;
      printf("%s\n", "*** Adição ***");
      break;
    case 2:
      operacao = subtracao;
      printf("%s\n", "*** Subtração ***");
      break;
    case 3:
      operacao = mutiplicacao;
      printf("%s\n", "*** Mutiplicação ***");
      break;
    case 4:
      operacao = divisao;
      printf("%s\n", "*** Divisão ***");
      break;
    case 5:
      operacao1P = parImpar;
      printf("%s\n", "*** Par ou Impar ***");
      break;
    case 0:
      exit(0);
      break;
    default:
      operacao = NULL;
      operacao1P = NULL;
      break;
    }

    if (operacao != NULL) {
      printf("Informe o 1º número: ");
      if (scanf("%d", &n1) != 1) {
        printf("Error: Entrada inválida.\n");
        while (getchar() != '\n'); // Limpa o buffer de entrada
        continue;
      }

      printf("Informe o 2º número: ");
      if (scanf("%d", &n2) != 1) {
        printf("Error: Entrada inválida.\n");
        while (getchar() != '\n'); // Limpa o buffer de entrada
        continue;
      }
      int r = executa(n1, n2, operacao);
      printf("O resultado é: %d\n\n\n", r);
    }

    if (operacao1P != NULL) {
      printf("Informe um número: ");
      if (scanf("%d", &n1) != 1) {
        printf("Error: Entrada inválida.\n");
        while (getchar() != '\n'); // Limpa o buffer de entrada
        continue;
      }
      char *r = (*operacao1P)(n1);
      printf("%s\n\n\n", r);
    }

    if ((operacao == NULL) && (operacao1P == NULL))
      printf("Opção inválida!\n\n\n");

    operacao = NULL;
    operacao1P = NULL;

    printf("0 - Sair | 1 - Continuar\n");
    scanf("%d", &opc);

  } while (opc != 0);
}

int executa(int n1, int n2, TFuncao *operacao) {
  int r = (*operacao)(n1, n2);
  return r;
}

char *executa1P(int n1, TFuncao1P *operacao) {
  char *r = (*operacao)(n1);
  return r;
}

int adicao(int x, int y) { return x + y; }

int subtracao(int x, int y) { return x - y; }

int mutiplicacao(int x, int y) { return x * y; }

int divisao(int x, int y) {
  if (y > 0) {
    return x / y;
  }
  return 0;
}

char *parImpar(int x) {
  char *r = ((x % 2) == 0) ? "Par" : "Impar";
  return r;
}
