#include "../include/input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

UserInput readUserInput(char prompt[200], FILE *input) {
  char *value = NULL;
  size_t size = 0;
  UserInput usrInput;

  printf("%s\n", prompt);
  ssize_t count = getline(&value, &size, input);

  if (count == -1) {
    usrInput.value = NULL;
    usrInput.size = 0;
    usrInput.count = 0;

    return usrInput;
  }

  value[count - 1] = 0; // Remove the \n

  usrInput.value = value;
  usrInput.size = size;
  usrInput.count = count;

  return usrInput;
}
