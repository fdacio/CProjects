#include <stdio.h>

float sum(int x, int y);
int calc(int *a, int *b);

int main() {
  float x, y;
  int *a, *b;

  x = 2.366;
  y = 3.5;
  int n1 = 8;
  int n2 = 2;

  printf("sum()  -> %.2f\n", sum(x, y));
  printf("calc() -> %d\n", calc(&n1, &n2));
}

float sum(int x, int y) {
  int _rsum = x + y;
  return _rsum;
}

int calc(int *a, int *b) {
  int _rcalc = (*a) * (*b);
  return _rcalc;
}