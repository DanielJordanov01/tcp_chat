#include "util.h"
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

struct AcceptedSocket {
  int acceptedSocketFD;
  struct sockaddr_in address;
  int error;
  bool acceptedSuccessfull;
};

struct AcceptedSocket *acceptIncomingConnection(int serverSocketFD);
void receiveAndPrintIncomingDataOnSeparateThread(
    struct AcceptedSocket *pSocket);
void *receiveAndPrintIncomingData(void *socketFD);
void startAcceptingIncomingConnections(int socketFD);
void acceptNewConnectionAndReceiveAndPrintItsData(int serverSocketFD);
void sendReceivedMessageToOtherClients(char *buffer, int socketFD);

struct AcceptedSocket acceptedSockets[10];
int acceptedSocketsCount = 0;

int main() {
  int serverSocketFD = createTCPIpv4Socket();

  char *ip = "";
  int port = 2000;
  struct sockaddr_in *serverAddress = createTCPIpv4Address(ip, port);

  int result = bind(serverSocketFD, serverAddress, sizeof(*serverAddress));
  if (result == 0)
    printf("Server socket bound successfully \n");

  int backlogAmount = 10;
  int listenResult = listen(serverSocketFD, backlogAmount);
  if (listenResult == 0) {
    printf("Listening... \n");
  }

  startAcceptingIncomingConnections(serverSocketFD);

  shutdown(serverSocketFD, SHUT_RDWR);
  printf("Client disconnected \n");

  return 0;
}

void startAcceptingIncomingConnections(int serverSocketFD) {
  while (true) {
    struct AcceptedSocket *clientSocket =
        acceptIncomingConnection(serverSocketFD);

    acceptedSockets[acceptedSocketsCount++] = *clientSocket;

    receiveAndPrintIncomingDataOnSeparateThread(clientSocket);
  }
}

void receiveAndPrintIncomingDataOnSeparateThread(
    struct AcceptedSocket *pSocket) {
  pthread_t id;
  int *fd = malloc(sizeof(int));
  *fd = pSocket->acceptedSocketFD;

  pthread_create(&id, NULL, receiveAndPrintIncomingData, fd);
}

void sendReceivedMessageToOtherClients(char *buffer, int socketFD) {
  for (int i = 0; i < acceptedSocketsCount; i++) {
    if (acceptedSockets[i].acceptedSocketFD != socketFD) {
      send(acceptedSockets[i].acceptedSocketFD, buffer, strlen(buffer), 0);
    }
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

      sendReceivedMessageToOtherClients(buffer, socketFD);
    }

    if (amountReceived == 0) {
      break;
    }
  }

  close(socketFD);
  printf("Client with socketFD %d disconnected\n", socketFD);

  return NULL;
}

struct AcceptedSocket *acceptIncomingConnection(int serverSocketFD) {
  struct sockaddr_in clientAddress;
  int clientAddressSize = sizeof(struct sockaddr_in);
  int clientSocketFD =
      accept(serverSocketFD, &clientAddress, &clientAddressSize);
  printf("Client with socketFD %d connected successfully\n", clientSocketFD);

  struct AcceptedSocket *acceptedSocket = malloc(sizeof(struct AcceptedSocket));
  acceptedSocket->address = clientAddress;
  acceptedSocket->acceptedSocketFD = clientSocketFD;
  acceptedSocket->acceptedSuccessfull = clientSocketFD > 0;

  if (!acceptedSocket->acceptedSuccessfull)
    acceptedSocket->error = clientSocketFD;

  return acceptedSocket;
}
