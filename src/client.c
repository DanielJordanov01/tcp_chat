#include "../include/config.h"
#include "../include/connection.h"
#include "../include/macros.h"
#include "../include/message.h"
#include "../include/threading.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int socketFD = createTCPIpv4Socket();
  Config config = parseArgs(argc, argv);

  if (!config.valid) {
    fprintf(stderr, "Invalid or missing arguments: %s <ip> <port>\n", argv[0]);
    return 1;
  }

  struct sockaddr_in address = createTCPIpv4Address(config.ip, config.port);

  int result = connect(socketFD, (struct sockaddr *)&address, sizeof(address));
  CHECK_UNRECOVERABLE_ERROR(result != 0, "Failed to connect to server");

  printf("connection was successfull \n");

  workOnNewThread(socketFD, listenAndPrint);
  readAndSendLine(socketFD);

  int closeResult = close(socketFD);
  CHECK_UNRECOVERABLE_ERROR(closeResult != 0, "Failed to close socket");

  return 0;
}
