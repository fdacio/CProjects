#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long long fatorial(unsigned int n);
// 8 -> 8 * 7 * 6 ..... * 1
/**
argc - arguments count
argv - arguments values
*/

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("Uso: %s <numero>\n", argv[0]);
    return 1;
  }

  char *end;
  errno = 0;
  int n = strtol(argv[1], &end, 10);

  if (errno != 0 || *end != '\0') {
    printf("Entrada inválida\n");
    return 1;
  }

  if (n < 0) {
    printf("Parâmetro deve ser um número inteiro não negativo\n");
    return 1;
  }

  printf("Fatorial(%d)=%llu\n", n, fatorial(n));
  return 0;
}

unsigned long long fatorial(unsigned int n) {

  if (n > 20) {
    printf("Erro: valor máximo é 20!\n");
    exit(1);
  }

  if ((n == 0) || (n == 1)) {
    return 1;
  }

  return n * fatorial(n - 1);
}
