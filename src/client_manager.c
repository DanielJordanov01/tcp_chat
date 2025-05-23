#include "../include/client_manager.h"
#include <string.h>
#include <strings.h>

void initClientManager(ClientManager *manager) { manager->count = 0; }

int getClientCount(ClientManager *manager) { return manager->count; }

Client *addClient(ClientManager *manager, AcceptedSocket socket) {
  if (manager->count >= MAX_CLIENTS)
    return NULL;

  Client *client = &manager->clients[manager->count++];
  client->socket = socket;
  client->id = manager->count;
  client->connected = 1;
  strcpy(client->name, "Unknown");

  return client;
}

int removeClientByFD(ClientManager *manager, int socketFD) {
  for (int i = 0; i < manager->count; i++) {
    if (manager->clients[i].socket.acceptedSocketFD == socketFD) {
      manager->clients[i] = manager->clients[manager->count - 1];
      manager->count--;
      return 1;
    }
  }
  return 0;
}

Client *getClientByID(ClientManager *manager, int id) {
  for (int i = 0; i < manager->count; i++) {
    if (manager->clients[i].id == id) {
      return &manager->clients[i];
    }
  }
  return NULL;
}
