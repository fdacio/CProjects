#include "valid_input.h"
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TValidateInputReturn validate_input(const char *input) {

  TValidateInputReturn result;

  if (input == NULL || *input == '\0') {
    result.value = NULL;
    snprintf(result.message, sizeof(result.message), "Valor informado é inválido: '%s'", input);
    return result;
  }

  char *ptr = NULL;
  ptr = (char *)input;
  while (*ptr) { 
    if ((ptr == input) && (*ptr == '-' || *ptr == '+')) {
      ptr++;
    }
    if (!isdigit(*ptr)) {
      snprintf(result.message, sizeof(result.message), "Valor informado é inválido: '%s'", input);
      result.value = NULL;
      return result; // Se o caractere não for um dígito, retorna falso
    }
    ptr++; // Move para o próximo caractere
  }

  long value = strtol(input, NULL, 10);
  if (value < 0 || value > UINT_MAX) {
    snprintf(result.message, sizeof(result.message), "Fora do intervalo : 0 a %u", UINT_MAX);
    result.value = NULL;
    return result;
  }

  result.value = &value;
  return result; // Entrada válida
}
