#include "../include/config.h"
#include "../include/connection.h"
#include "../include/macros.h"
#include "../include/server_handler.h"
#include "../include/server_setup.h"

#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <unistd.h>

AcceptedSocket acceptedSockets[10];
int acceptedSocketsCount = 0;

int main(int argc, char *argv[]) {
  Config config = parseArgs(argc, argv);
  CHECK_UNRECOVERABLE_ERROR(!config.valid,
                            "Invalid or missing arguments: %s <ip> <port>");
  int socketFD = initServer(config.ip, config.port);

  runServerLoop(socketFD);
  shutdownServer(socketFD);

  return 0;
}
