#include "../include/config.h"
#include "../include/connection.h"
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

  if (result == 0)
    printf("connection was successfull \n");

  workOnNewThread(socketFD, listenAndPrint);
  readAndSendLine(socketFD);

  close(socketFD);

  return 0;
}
