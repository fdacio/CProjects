#ifndef VALID_INPUT_H
#define VALID_INPUT_H

typedef struct ValidateInput {
  char message[100];
  long *value;
} TValidateInputReturn;


TValidateInputReturn validate_input(const char *input);

#endif

