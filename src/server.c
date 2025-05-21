#include "../include/config.h"
#include "../include/connection.h"
#include "../include/macros.h"
#include "../include/message.h"
#include "../include/threading.h"

#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

void *receiveAndPrintIncomingData(void *socketFD);
void startAcceptingIncomingConnections(int socketFD);
void acceptNewConnectionAndReceiveAndPrintItsData(int serverSocketFD);
void removeDisconnectedClient(int socketFD);
void disconnectClient(int socketFD);

AcceptedSocket acceptedSockets[10];
int acceptedSocketsCount = 0;

int main(int argc, char *argv[]) {
  int serverSocketFD = createTCPIpv4Socket();
  Config config = parseArgs(argc, argv);
  CHECK_UNRECOVERABLE_ERROR(!config.valid,
                            "Invalid or missing arguments: %s <ip> <port>");

  struct sockaddr_in serverAddress =
      createTCPIpv4Address(config.ip, config.port);

  int result = bind(serverSocketFD, (struct sockaddr *)&serverAddress,
                    sizeof(serverAddress));
  CHECK_UNRECOVERABLE_ERROR(result != 0, "Failed to bind server socket");
  printf("Server socket bound successfully \n");

  int backlogAmount = 10;
  int listenResult = listen(serverSocketFD, backlogAmount);
  if (listenResult == 0) {
    printf("Listening... \n");
  }

  startAcceptingIncomingConnections(serverSocketFD);

  int shutResult = shutdown(serverSocketFD, SHUT_RDWR);
  if (shutResult != 0) {
    perror("Error shutting down server socket");
  } else {
    printf("Server stopped \n");
  }

  return 0;
}

void startAcceptingIncomingConnections(int serverSocketFD) {
  while (true) {
    AcceptedSocket clientSocket = acceptIncomingConnection(serverSocketFD);

    acceptedSockets[acceptedSocketsCount++] = clientSocket;

    workOnNewThread(clientSocket.acceptedSocketFD, receiveAndPrintIncomingData);
  }
}

void *receiveAndPrintIncomingData(void *arg) {
  int socketFD = *(int *)arg;
  free(arg);

  char buffer[1024];
  while (true) {
    ssize_t amountReceived = recv(socketFD, buffer, 1024, 0);

    if (amountReceived > 0) {
      buffer[amountReceived] = 0;
      printf("Response was %s\n", buffer);

      sendReceivedMessageToOtherClients(buffer, socketFD, acceptedSockets,
                                        acceptedSocketsCount);
    }

    if (amountReceived == 0) {
      break;
    }

    if (amountReceived < 0) {
      perror("There was an error with received message");
    }
  }

  disconnectClient(socketFD);

  return NULL;
}

void disconnectClient(int socketFD) {
  int closeResult = close(socketFD);
  if (closeResult == 0) {
    removeDisconnectedClient(socketFD);
    printf("Client with socketFD %d disconnected\n", socketFD);
  } else
    fprintf(stderr, "Failed to disconnect client with socketFD %d", socketFD);
}

void removeDisconnectedClient(int socketFD) {
  for (int i = 0; i < acceptedSocketsCount; i++) {
    if (acceptedSockets[i].acceptedSocketFD == socketFD) {
      acceptedSockets[i] = acceptedSockets[i + 1];
      acceptedSocketsCount--;
    }
  }
}
