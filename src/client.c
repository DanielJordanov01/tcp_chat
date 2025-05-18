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

int main() {
  int socketFD = createTCPIpv4Socket();

  char *ip = "127.0.0.1";
  struct sockaddr_in *address = createTCPIpv4Address(ip, 2000);

  int result = connect(socketFD, address, sizeof(*address));

  if (result == 0)
    printf("connection was successfull \n");

  workOnNewThread(socketFD, listenAndPrint);
  readAndSendLine(socketFD);

  close(socketFD);

  return 0;
}
