#ifndef VALID_INPUT_H
#define VALID_INPUT_H

typedef struct ValidateInput {
  char message[100];
  int isValid;
  long value;
} TValidateInput;

TValidateInput validate_input(const char *input);

#endif

