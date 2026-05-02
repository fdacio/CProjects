#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

long fatorial(int n);
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
  if (n == 0 || n == 1) {
    printf("Fatorial(%d)=1\n", n);
    return 0;
  }
  if (n > 20) {
    printf("Parâmetro máximo: 20\n");
    return 1;
  }

  long r = fatorial(n);
  printf("Fatorial(%d)=%ld\n", n, r);
  return 0;
}

long fatorial(int n) {

  if ((n == 0) || (n == 1)) {
    return 1;
  }

  long r = n * fatorial(n - 1);
  return r;
}
