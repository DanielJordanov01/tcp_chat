#include "../include/input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct UserInput *readUserInput(char prompt[200]) {
  char *value = NULL;
  size_t size = 0;

  printf("%s\n", prompt);
  ssize_t count = getline(&value, &size, stdin);

  if (count == -1) {
    free(value);
    return NULL;
  }

  value[count - 1] = 0; // Remove the \n

  // This allocates a single block for both the struct + string so that we only
  // free the usrInput
  size_t totalSize = sizeof(struct UserInput) + count;
  struct UserInput *usrInput = malloc(totalSize);

  if (!usrInput) {
    free(value);
    return NULL;
  }

  usrInput->value = (char *)(usrInput + 1);
  memcpy(usrInput->value, value, count);

  usrInput->size = size;
  usrInput->count = count;

  free(value);

  return usrInput;
}
