#include "../include/client_setup.h"
#include "../include/connection.h"
#include "../include/macros.h"

#include <unistd.h>

int initClient(char *ip, int port) {
  int socketFD = createTCPIpv4Socket();

  struct sockaddr_in address = createTCPIpv4Address(ip, port);

  CHECK_UNRECOVERABLE_ERROR(
      connect(socketFD, (struct sockaddr *)&address, sizeof(address)),
      "Failed to connect to server");

  printf("connection was successfull \n");

  return socketFD;
}

void disconnect(int socketFD) {
  CHECK_UNRECOVERABLE_ERROR(close(socketFD), "Failed to close socket");
}
