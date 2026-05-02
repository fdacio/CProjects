#include "valid_input.h"
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TValidateInput validate_input(const char *input) {

  TValidateInput result = {.message = "", .isValid = 0, .value = 0};

  if (input == NULL || *input == '\0') {
    snprintf(result.message, sizeof(result.message),
             "Valor informado é inválido: '%s'", input);
    result.isValid = 0;
    return result;
  }

  char *ptr = NULL;
  ptr = (char *)input;
  while (*ptr) {
    if ((ptr == input) && (*ptr == '-' || *ptr == '+')) {
      ptr++;
    }
    if (*ptr == '\0') { // garante que não é só sinal
      snprintf(result.message, sizeof(result.message),
               "Valor informado é inválido: '%s'", input);
      result.isValid = 0;
      return result;
    }
    if (!isdigit(*ptr)) {
      snprintf(result.message, sizeof(result.message),
               "Valor informado é inválido: '%s'", input);
      result.isValid = 0;
      return result; // Se o caractere não for um dígito, retorna falso
    }
    ptr++; // Move para o próximo caractere
  }

  errno = 0;
  char *endptr;
  long value = strtol(input, &endptr, 10);

  if (*endptr != '\0') {
    snprintf(result.message, sizeof(result.message), "Valor inválido: '%s'",
             input);
    result.isValid = 0;
    return result;
  }

  if (errno == ERANGE) {
    snprintf(result.message, sizeof(result.message),
             "Fora do intervalo : 0 a %u", UINT_MAX);
    result.isValid = 0;
    return result;
  }

  if (value < 0 || value > UINT_MAX) {
    snprintf(result.message, sizeof(result.message),
             "Fora do intervalo : 0 a %u", UINT_MAX);
    result.isValid = 0;
    return result;
  }

  result.value = value;
  result.message[0] = '\0'; // Limpa a mensagem de erro
  result.isValid = 1;
  return result; // Entrada válida
}
