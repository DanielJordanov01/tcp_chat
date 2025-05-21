#include "../include/server_setup.h"
#include "../include/connection.h"
#include "../include/macros.h"

int initServer(char *ip, int port) {
  int serverSocketFD = createTCPIpv4Socket();
  struct sockaddr_in address = createTCPIpv4Address(ip, port);

  CHECK_UNRECOVERABLE_ERROR(
      bind(serverSocketFD, (struct sockaddr *)&address, sizeof(address)) != 0,
      "Failed to bind server socket");

  CHECK_UNRECOVERABLE_ERROR(listen(serverSocketFD, 10) != 0,
                            "Failed to listen on server socket");

  printf("Server ready at %s:%d\n", ip, port);
  return serverSocketFD;
}

void shutdownServer(int socketFD) {
  if (shutdown(socketFD, SHUT_RDWR) != 0)
    perror("Failed to shutdown server");
  else
    printf("Server shut down cleanly\n");
}
