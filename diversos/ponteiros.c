#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  char c = 'A';
  char *_pointer1 = &c;
  char *_pointer2 = _pointer1 + 1;
  printf("%p\n", (void *)&_pointer1);
  printf("%p\n", (void *)&_pointer2);
  printf("%p\n", (void *)_pointer1);
  printf("%c\n", *_pointer1);

  printf("Ponteiros para strings\n");
  char *p1;
  char text[80] = "C completo e total";
  printf("%s\n", text);
  printf("%p\n", (void *)text);

  p1 = text;
  printf("%p\n", (void *)p1);
  printf("%p\n", (void *)p1);

  printf("\n\nPonteiros para inteiros\n");
  int *p2;
  int numbers[5] = {1, 2, 3, 4, 5};

  p2 = numbers;
  while (*p2) {
    printf("%d|%p - ", *p2, (void *)p2);
    p2++;
  }
  printf("\n");

  p2 = numbers;
  printf("%d\n", *numbers);
  printf("%p\n", (void *)numbers);
  printf("%p\n", (void *)++p2);
  printf("%p\n", (void *)++p2);

  /*
  char *text;
  text = (char*) malloc(80 * sizeof(char));
  if (!text) {
      printf("Memory erro!");
      return 1;
  }
  */
  do {
    p1 = text;
    printf("Informe uma palavra: ");
    fgets(text, sizeof(text), stdin);
    // scanf("%s", text);

    printf("Upper Case -> ");
    while (*p1) {
      char _pipe = (p1 == text ? '|' : (char)0);
      printf("%c%c|", _pipe, toupper(*p1++));
    }
    printf("\n");

    p1 = text;
    printf("ASCII -> ");
    while (*p1) {
      char _pipe = (p1 == text ? '|' : (char)0);
      char c = *p1;
      printf("%c%c:%d|", _pipe, c, c);
      p1++;
    }
    printf("\n");

    printf("Inverse -> ");
    char _pipe = (p1 == text ? '|' : (char)0);
    for (p1 = text + strlen(text) - 1; p1 >= text; p1--) {
      printf("%c%c|", _pipe, *(p1));
    }
    printf("\n");
    printf("--------------------------------------------------\n");
    printf("text: %s\n", text);

  } while (strcmp(text, "done\n") != 0 && strcmp(text, "done") != 0);

  printf("Fim do programa\n");
}
