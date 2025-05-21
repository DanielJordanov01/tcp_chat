#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <stdlib.h>

#define CHECK_UNRECOVERABLE_ERROR(condition, message)                          \
  do {                                                                         \
    if (condition) {                                                           \
      fprintf(stderr, "Error: %s (at %s:%d)\n", message, __FILE__, __LINE__);  \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)

#endif
