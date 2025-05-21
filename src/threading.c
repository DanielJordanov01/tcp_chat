#include <pthread.h>
#include <stdlib.h>

void workOnNewThread(int socketFD, void *(*fn)(void *)) {
  /*
    Allocated fd on the heap so that it lives long enough for the thread to
    access. Client must free
  */
  int *fd = malloc(sizeof(int));
  *fd = socketFD;

  pthread_t id;
  pthread_create(&id, NULL, fn, fd);
}
