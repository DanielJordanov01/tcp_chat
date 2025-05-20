#ifndef INPUT_H
#define INPUT_H

#include <unistd.h>

struct UserInput {
  char *value;
  size_t size;
  ssize_t count;
};
struct UserInput readUserInput(char prompt[200]);

#endif
