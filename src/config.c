#include "../include/config.h"
#include <stdlib.h>

Config parseArgs(int argc, char *argv[]) {
  Config config = {.ip = NULL, .port = 0, .valid = 0};

  if (argc >= 3) {
    config.ip = argv[1];

    int port = atoi(argv[2]);
    if (port == 0) {
      return config;
    }

    config.valid = 1;
    config.port = atoi(argv[2]);
  }

  return config;
}
