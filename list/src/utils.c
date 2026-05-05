#define _XOPEN_SOURCE 700
#define _POSIX_C_SOURCE 199309L

#include "utils.h"
#include <locale.h> // setlocale
#include <stdio.h>
#include <stdlib.h> // mbstowcs
#include <string.h>
#include <time.h>
#include <wchar.h> // wchar_t, wcwidth
#include <ctype.h>

/* Calcula largura visual (colunas) */
int utf8_width(const char *str) {
  wchar_t wstr[256];
  mbstowcs(wstr, str, 256);

  int width = 0;
  for (int i = 0; wstr[i] != L'\0'; i++) {
    int w = wcwidth(wstr[i]);
    if (w > 0)
      width += w;
  }
  return width;
}

void print_utf8(const char *str, int width) {
  int w = utf8_width(str);
  printf("%s", str);

  for (int i = 0; i < (width - w); i++) {
    printf(" ");
  }
}

/* Substitui caracteres acentuados por não acentuados */
void sanitize_string(char *str) {
  unsigned char *p = (unsigned char *)str;

  while (*p) {

    // UTF-8: caracteres acentuados começam com 0xC3
    if (*p == 0xC3) {
      unsigned char next = *(p + 1);

      switch (next) {
      // a
      case 0xA1:
      case 0xA0:
      case 0xA2:
      case 0xA3:
      case 0xA4:
        *p = 'a';
        break;
      case 0x81:
      case 0x80:
      case 0x82:
      case 0x83:
      case 0x84:
        *p = 'A';
        break;

      // e
      case 0xA9:
      case 0xAA:
      case 0xA8:
      case 0xAB:
        *p = 'e';
        break;
      case 0x89:
      case 0x8A:
      case 0x88:
      case 0x8B:
        *p = 'E';
        break;

      // i
      case 0xAD:
      case 0xAE:
      case 0xAC:
      case 0xAF:
        *p = 'i';
        break;
      case 0x8D:
      case 0x8E:
      case 0x8C:
      case 0x8F:
        *p = 'I';
        break;

      // o
      case 0xB3:
      case 0xB2:
      case 0xB4:
      case 0xB5:
      case 0xB6:
        *p = 'o';
        break;
      case 0x93:
      case 0x92:
      case 0x94:
      case 0x95:
      case 0x96:
        *p = 'O';
        break;

      // u
      case 0xBA:
      case 0xB9:
      case 0xBB:
      case 0xBC:
        *p = 'u';
        break;
      case 0x9A:
      case 0x99:
      case 0x9B:
      case 0x9C:
        *p = 'U';
        break;

      // c
      case 0xA7:
        *p = 'c';
        break;
      case 0x87:
        *p = 'C';
        break;

      default:
        *p = '?'; // fallback
      }

      // remove o segundo byte (compacta string)
      memmove(p + 1, p + 2, strlen((char *)p + 2) + 1);
    }

    p++;
  }
}

/* Convert uma string para todos o caracteres minúsculos */
void to_lower_case(char *str) {
  while (*str) {
    *str = tolower(*str);
    str++;
  }
}

/* Retorna tempo atual em ms */
long long now_ms() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);

  return (long long)ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

long long now_ns() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}