#include "../include/server_handler.h"
#include "../include/connection.h"
#include "../include/message.h"
#include "../include/threading.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Max number of clients
#define MAX_CLIENTS 10

static AcceptedSocket acceptedSockets[MAX_CLIENTS];
static int acceptedSocketsCount = 0;

static void removeDisconnectedClient(int socketFD) {
  for (int i = 0; i < acceptedSocketsCount; i++) {
    if (acceptedSockets[i].acceptedSocketFD == socketFD) {
      for (int j = i; j < acceptedSocketsCount - 1; j++) {
        acceptedSockets[j] = acceptedSockets[j + 1];
      }
      acceptedSocketsCount--;
      break;
    }
  }
}

static void disconnectClient(int socketFD) {
  if (close(socketFD) == 0) {
    removeDisconnectedClient(socketFD);
    printf("Client with socketFD %d disconnected\n", socketFD);
  } else {
    perror("Failed to close client socket");
  }
}

static void *receiveAndPrintIncomingData(void *arg) {
  int socketFD = *(int *)arg;
  free(arg);

  char buffer[1024];
  while (1) {
    ssize_t received = recv(socketFD, buffer, sizeof(buffer) - 1, 0);

    if (received > 0) {
      buffer[received] = '\0';
      sendReceivedMessageToOtherClients(buffer, socketFD, acceptedSockets,
                                        acceptedSocketsCount);
    } else if (received == 0) {
      break;
    } else {
      perror("recv error");
      break;
    }
  }

  disconnectClient(socketFD);
  return NULL;
}

void runServerLoop(int serverSocketFD) {
  while (true) {
    if (acceptedSocketsCount >= MAX_CLIENTS) {
      printf("Max clients reached. New connections will be rejected.\n");
      sleep(1);
      continue;
    }

    AcceptedSocket clientSocket = acceptIncomingConnection(serverSocketFD);
    if (!clientSocket.acceptedSuccessfull) {
      perror("Failed to accept client");
      continue;
    }

    acceptedSockets[acceptedSocketsCount++] = clientSocket;

    workOnNewThread(clientSocket.acceptedSocketFD, receiveAndPrintIncomingData);
  }
}
