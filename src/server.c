#include "../include/connection.h"
#include "../include/message.h"
#include "../include/threading.h"

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
    struct AcceptedSocket clientSocket =
        acceptIncomingConnection(serverSocketFD);

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
  }

  close(socketFD);
  printf("Client with socketFD %d disconnected\n", socketFD);

  return NULL;
}
