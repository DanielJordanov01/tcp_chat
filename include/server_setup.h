#ifndef SERVER_SETUP_H
#define SERVER_SETUP_H

int initServer(char *ip, int port);
void shutdownServer(int socketFD);

#endif
