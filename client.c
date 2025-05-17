#include "util.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void readAndSendLine(int socketFD);
void *listenAndPrint(void *socketFD);
void startListeningAndPrintMessagesOnNewThread(int socketFD);

int main() {
  int socketFD = createTCPIpv4Socket();

  char *ip = "127.0.0.1";
  struct sockaddr_in *address = createTCPIpv4Address(ip, 2000);

  int result = connect(socketFD, address, sizeof(*address));

  if (result == 0)
    printf("connection was successfull \n");

  startListeningAndPrintMessagesOnNewThread(socketFD);
  readAndSendLine(socketFD);

  close(socketFD);

  return 0;
}

void *listenAndPrint(void *arg) {
  int socketFD = *(int *)arg;
  free(arg);

  char buffer[1024];
  while (true) {
    ssize_t amountReceived = recv(socketFD, buffer, 1024, 0);

    if (amountReceived > 0) {
      buffer[amountReceived] = 0;
      printf("%s\n", buffer);
    }

    if (amountReceived == 0) {
      break;
    }
  }

  close(socketFD);

  return NULL;
}

void startListeningAndPrintMessagesOnNewThread(int socketFD) {
  int *fd = malloc(sizeof(int));
  *fd = socketFD;

  pthread_t id;
  pthread_create(&id, NULL, listenAndPrint, fd);
}

void readAndSendLine(int socketFD) {
  char *name = NULL;
  size_t nameSize = 0;
  printf("Please enter your name\n");
  ssize_t nameCount = getline(&name, &nameSize, stdin);
  name[nameCount - 1] = 0; // Remove the \n

  char *line = NULL;
  size_t lineSize = 0;
  printf("Type what to send(type exit to exit)...\n");

  char buffer[1024];

  while (true) {
    ssize_t charCount = getline(&line, &lineSize, stdin);
    line[charCount - 1] = 0; // Remove the \n

    sprintf(buffer, "%s: %s", name, line);

    if (charCount > 0) {
      if (strcmp(line, "exit") == 0)
        break;

      ssize_t amountWasSent = send(socketFD, buffer, strlen(buffer), 0);
    }
  }
}
