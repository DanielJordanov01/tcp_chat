#include "../include/connection.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

struct sockaddr_in *createTCPIpv4Address(char *ip, int port) {
  struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
  address->sin_family = AF_INET;
  address->sin_port = htons(port);

  if (strlen(ip) == 0)
    address->sin_addr.s_addr = INADDR_ANY;
  else
    inet_pton(AF_INET, ip, &address->sin_addr.s_addr);

  return address;
}

int createTCPIpv4Socket() { return socket(AF_INET, SOCK_STREAM, 0); }

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
