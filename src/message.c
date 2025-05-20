#include "../include/connection.h"
#include "../include/input.h"

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
  struct UserInput name = readUserInput("Please enter your name");
  char buffer[1024];

  while (true) {
    struct UserInput message =
        readUserInput("Type what to send(type exit to exit)...");

    sprintf(buffer, "%s: %s", name.value, message.value);

    if (message.count > 0) {
      if (strcmp(message.value, "exit") == 0)
        break;

      ssize_t amountWasSent = send(socketFD, buffer, strlen(buffer), 0);
    }

    free(message.value);
  }

  free(name.value);
}
