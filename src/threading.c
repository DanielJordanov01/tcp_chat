#include "../include/threading.h"
#include "../include/client_manager.h"
#include "../include/macros.h"

#include <pthread.h>
#include <stdlib.h>

void workOnNewThread(int socketFD, ClientManager *manager,
                     void *(*fn)(void *)) {
  /*
    Allocated threadArgs on the heap so that it lives long enough for the thread
    to access. Client must free
  */
  ThreadArgs *args = malloc(sizeof(ThreadArgs));
  args->manager = manager;
  args->socketFD = socketFD;

  pthread_t id;
  int error = pthread_create(&id, NULL, fn, args);
  CHECK_UNRECOVERABLE_ERROR(error != 0, "Failed to start a new thread");
}
