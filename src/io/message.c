#include "app/client_manager.h"
#include "io/input.h"
#include "net/connection.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void sendReceivedMessageToOtherClients(char *buffer, int socketFD,
                                       Client clients[MAX_CLIENTS],
                                       int acceptedSocketsCount) {
  for (int i = 0; i < acceptedSocketsCount; i++) {
    if (clients[i].socket.acceptedSocketFD != socketFD) {
      send(clients[i].socket.acceptedSocketFD, buffer, strlen(buffer), 0);
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

  return NULL;
}

void readAndSendLine(int socketFD) {
  UserInput name = readUserInput("Please enter your name", stdin);
  char buffer[1024];

  while (true) {
    UserInput message =
        readUserInput("Type what to send(type exit to exit)...", stdin);

    snprintf(buffer, 1024, "%s: %s", name.value, message.value);

    if (message.count > 0) {
      if (strcmp(message.value, "exit") == 0)
        break;

      ssize_t amountWasSent = send(socketFD, buffer, strlen(buffer), 0);
      if (amountWasSent == 0) {
        printf("Error: nothing sent\n");
      }
    }

    free(message.value);
  }

  free(name.value);
}
