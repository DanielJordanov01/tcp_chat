#include "app/client_manager.h"
#include "app/server_handler.h"
#include "app/server_setup.h"
#include "core/config.h"
#include "core/macros.h"
#include "net/connection.h"

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

  ClientManager manager;
  initClientManager(&manager);

  runServerLoop(&manager, socketFD);
  shutdownServer(socketFD);

  return 0;
}
