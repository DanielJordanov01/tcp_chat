#include "app/server_handler.h"
#include "app/client_manager.h"
#include "io/message.h"
#include "net/connection.h"
#include "threading/threading.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void disconnectClient(ClientManager *manager, int socketFD) {
  if (close(socketFD) == 0) {
    removeClientByFD(manager, socketFD);
    printf("Client with socketFD %d disconnected\n", socketFD);
  } else {
    perror("Failed to close client socket");
  }
}

static void *receiveAndPrintIncomingData(void *arg) {
  ThreadArgs *args = (ThreadArgs *)arg;

  char buffer[1024];
  while (1) {
    ssize_t received = recv(args->socketFD, buffer, sizeof(buffer) - 1, 0);

    if (received > 0) {
      buffer[received] = '\0';
      sendReceivedMessageToOtherClients(buffer, args->socketFD,
                                        args->manager->clients,
                                        getClientCount(args->manager));
    } else if (received == 0) {
      break;
    } else {
      perror("recv error");
      break;
    }
  }

  disconnectClient(args->manager, args->socketFD);
  free(arg);

  return NULL;
}

void runServerLoop(ClientManager *manager, int serverSocketFD) {
  while (true) {
    if (manager->count >= MAX_CLIENTS) {
      printf("Max clients reached. New connections will be rejected.\n");
      sleep(1);
      continue;
    }

    AcceptedSocket clientSocket = acceptIncomingConnection(serverSocketFD);
    if (!clientSocket.acceptedSuccessfull) {
      perror("Failed to accept client");
      continue;
    }

    addClient(manager, clientSocket);

    workOnNewThread(clientSocket.acceptedSocketFD, manager,
                    receiveAndPrintIncomingData);
  }
}
