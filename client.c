#include "util.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int socketFD = createTCPIpv4Socket();

  char *ip = "127.0.0.1";
  struct sockaddr_in *address = createTCPIpv4Address(ip, 2000);

  int result = connect(socketFD, address, sizeof(*address));

  if (result == 0)
    printf("connection was successfull \n");

  char *line = NULL;
  size_t lineSize = 0;
  printf("Type what to send(type exit to exit)...\n");

  while (true) {
    ssize_t charCount = getline(&line, &lineSize, stdin);

    if (charCount > 0) {
      if (strcmp(line, "exit\n") == 0)
        break;

      ssize_t amountWasSent = send(socketFD, line, charCount, 0);
    }
  }

  close(socketFD);

  return 0;
}
