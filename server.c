#include "util.h"
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

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

  struct sockaddr_in clientAddress;
  int clientAddressSize = sizeof(struct sockaddr_in);
  int clientSocketFD =
      accept(serverSocketFD, &clientAddress, &clientAddressSize);
  printf("Client with socketFD %d connected successfully\n", clientSocketFD);

  char buffer[1024];
  while (true) {
    ssize_t amountReceived = recv(clientSocketFD, buffer, 1024, 0);

    if (amountReceived > 0) {
      buffer[amountReceived] = 0;
      printf("Response was %s\n", buffer);
    }

    if (amountReceived == 0) {
      break;
    }
  }

  close(clientSocketFD);
  shutdown(serverSocketFD, SHUT_RDWR);
  printf("Client with socketFD %d disconnected \n", clientSocketFD);

  return 0;
}
