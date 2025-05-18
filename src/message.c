#include "../include/connection.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void sendReceivedMessageToOtherClients(
    char *buffer, int socketFD, struct AcceptedSocket acceptedSockets[10],
    int acceptedSocketsCount) {
  for (int i = 0; i < acceptedSocketsCount; i++) {
    if (acceptedSockets[i].acceptedSocketFD != socketFD) {
      send(acceptedSockets[i].acceptedSocketFD, buffer, strlen(buffer), 0);
    }
  }
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
