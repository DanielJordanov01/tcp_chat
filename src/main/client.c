#include "app/client_setup.h"
#include "core/config.h"
#include "core/macros.h"
#include "io/message.h"
#include "threading/threading.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  Config config = parseArgs(argc, argv);
  CHECK_UNRECOVERABLE_ERROR(!config.valid,
                            "Invalid or missing arguments: %s <ip> <port>");

  int socketFD = initClient(config.ip, config.port);

  workOnNewThread(socketFD, NULL, listenAndPrint);
  readAndSendLine(socketFD);

  disconnect(socketFD);

  return 0;
}
