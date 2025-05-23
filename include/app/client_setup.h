#ifndef SERVER_SETUP_H
#define SERVER_SETUP_H

int initClient(char *ip, int port);
void disconnect(int socketFD);

#endif
