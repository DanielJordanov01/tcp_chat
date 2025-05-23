#ifndef THREADING_H
#define THREADING_H

#include "app/client_manager.h"

typedef struct {
  int socketFD;
  ClientManager *manager;
} ThreadArgs;

/**
 * @brief Launches a new thread to handle a socket using a provided function.
 *
 * Allocates memory for the socket file descriptor, stores it, and starts
 * a new thread that runs the provided function.
 *
 * @param socketFD The socket file descriptor to pass to the thread function.
 * @param fn Pointer to the thread function that takes a `void*` argument.
 *
 * @note The caller must ensure that the thread function properly frees the
 *       allocated memory for the file descriptor when done.
 */
void workOnNewThread(int socketFD, ClientManager *manager, void *(*fn)(void *));

#endif
