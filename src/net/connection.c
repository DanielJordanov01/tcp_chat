#include "net/connection.h"
#include "core/macros.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

struct sockaddr_in createTCPIpv4Address(char *ip, int port) {
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(port);

  if (strlen(ip) == 0)
    address.sin_addr.s_addr = INADDR_ANY;
  else {
    int result = inet_pton(AF_INET, ip, &address.sin_addr.s_addr);
    CHECK_UNRECOVERABLE_ERROR(result != 1,
                              "Unsuccessful network address conversion");
  }

  return address;
}

int createTCPIpv4Socket() { return socket(AF_INET, SOCK_STREAM, 0); }

AcceptedSocket acceptIncomingConnection(int serverSocketFD) {
  struct sockaddr_in clientAddress;
  socklen_t clientAddressSize = sizeof(struct sockaddr_in);
  int clientSocketFD = accept(serverSocketFD, (struct sockaddr *)&clientAddress,
                              &clientAddressSize);
  printf("Client with socketFD %d connected successfully\n", clientSocketFD);

  AcceptedSocket acceptedSocket;
  acceptedSocket.address = clientAddress;
  acceptedSocket.acceptedSocketFD = clientSocketFD;
  acceptedSocket.acceptedSuccessfull = clientSocketFD > 0;

  if (!acceptedSocket.acceptedSuccessfull)
    acceptedSocket.error = clientSocketFD;

  return acceptedSocket;
}
