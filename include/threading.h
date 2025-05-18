#ifndef THREADING_H
#define THREADING_H

void workOnNewThread(int socketFD, void *(*fn)(void *));

#endif
