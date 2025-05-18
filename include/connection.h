#ifndef UTIL_H
#define UTIL_H

#include <netinet/in.h>

struct sockaddr_in *createTCPIpv4Address(char *ip, int port);
int createTCPIpv4Socket();

#endif
