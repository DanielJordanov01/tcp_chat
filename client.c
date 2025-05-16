#include "util.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int main() {
  int socketFD = createTCPIpv4Socket();

  char *ip = "172.253.63.100";
  struct sockaddr_in *address = createTCPIpv4Address(ip, 80);

  int result = connect(socketFD, address, sizeof(*address));

  if (result == 0)
    printf("connection was successfull \n");

  char *message;
  message = "GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n";
  send(socketFD, message, strlen(message), 0);

  char buffer[1024];
  recv(socketFD, buffer, 1024, 0);

  printf("Response was %s\n", buffer);

  return 0;
}
