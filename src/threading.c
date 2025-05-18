#include <pthread.h>
#include <stdlib.h>

void workOnNewThread(int socketFD, void *(*fn)(void *)) {
  int *fd = malloc(sizeof(int));
  *fd = socketFD;

  pthread_t id;
  pthread_create(&id, NULL, fn, fd);
}
