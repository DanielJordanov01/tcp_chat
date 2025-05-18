#ifndef MESSAGE_H
#define MESSAGE_H

void sendReceivedMessageToOtherClients(char *buffer, int socketFD,
                                       struct AcceptedSocket acceptedSockets[],
                                       int acceptedSocketsCount);
void readAndSendLine(int socketFD);
void *listenAndPrint(void *socketFD);

#endif
