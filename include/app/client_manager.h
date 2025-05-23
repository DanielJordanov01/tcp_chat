#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include "net/connection.h"

#define MAX_CLIENTS 10

typedef struct {
  AcceptedSocket socket;
  int id;
  int connected;
  char name[100];
} Client;

typedef struct {
  Client clients[MAX_CLIENTS];
  int count;
} ClientManager;

void initClientManager(ClientManager *manager);
Client *addClient(ClientManager *manager, AcceptedSocket socket);
int removeClientByFD(ClientManager *manager, int socketFD);
Client *getClientByID(ClientManager *manager, int id);
int getClientCount(ClientManager *manager);

#endif
