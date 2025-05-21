#include "../include/client_setup.h"
#include "../include/config.h"
#include "../include/macros.h"
#include "../include/message.h"
#include "../include/threading.h"

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

  workOnNewThread(socketFD, listenAndPrint);
  readAndSendLine(socketFD);

  disconnect(socketFD);

  return 0;
}
