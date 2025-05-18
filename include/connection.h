#ifndef UTIL_H
#define UTIL_H

#include <netinet/in.h>
#include <stdbool.h>

struct AcceptedSocket {
  int acceptedSocketFD;
  struct sockaddr_in address;
  int error;
  bool acceptedSuccessfull;
};

struct sockaddr_in *createTCPIpv4Address(char *ip, int port);
int createTCPIpv4Socket();
struct AcceptedSocket *acceptIncomingConnection(int serverSocketFD);

#endif
