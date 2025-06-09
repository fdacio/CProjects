#include <stdio.h>
#include <string.h>

unsigned long toBinario(const unsigned int decimal); // versão sem recursividade
unsigned long toBinarioRV1(const unsigned int decimal); //recursiva versão 1
unsigned long toBinarioRV2(const unsigned int decimal); //recursiva versão 2

void main() {

  int decimal;
  char key;

  do {
    printf("**** Decimal para Binário **** \n");
    printf("Informe um número: ");
    scanf("%d", &decimal);
    // printf("%d em binário Funcao NRe é: %lu\n", decimal, toBinario(decimal));
    // printf("%d em binário Funcao RV1 é: %lu\n", decimal, toBinarioRV1(decimal));
    printf("%d em binário Funcao RV2 é: %lu\n\n\n", decimal, toBinarioRV2(decimal));
    scanf("%c", &key);

    printf("X para Sair | Enter para continuar\n");
    key = getchar();

    printf("\033[2J\033[H"); // limpa a tela

  } while ((key != 'X') && (key != 'x'));
}

unsigned long toBinario(const unsigned int decimal) {
  unsigned long _binary = 0;
  int _dec = 1;
  unsigned int _decimal = decimal;
  while (_decimal > 0) {
    unsigned int r = _decimal % 2;
    _binary = (_dec * r) + _binary;
    _dec = _dec * 10;
    _decimal = _decimal / 2;
    //printf("\nbin->%lu\n", _binary);
  }
  return _binary;
}

/**
 * A chamada recursiva usa uma pilha.
 * Na primeira da um push na pilha com o resultado
 * 
 */
unsigned long toBinarioRV1(const unsigned int decimal) {
    if (decimal == 0) return 0;
    return (decimal % 2) + 10 * toBinarioRV1(decimal/2); 
}

unsigned long toBinarioRV2(const unsigned int decimal) {
    if (decimal == 0) return 0;
    int resto = decimal % 2;
    unsigned long binario = resto + 10 * toBinarioRV2(decimal/2); 
    printf("dec->%d\n",  decimal);
    printf("res->%d\n",  resto);
    printf("bin->%lu\n", binario);
    printf("%4c\n", '-');
    return binario;
}


unsigned int fatorial(int n) {
  if (n == 0) {
    return 1; // Caso base: fatorial de 0 é 1
  } else {
    return n * fatorial(n - 1); // Chamada recursiva: calcula fatorial de (n-1)
  }
}