#ifndef MESSAGE_H
#define MESSAGE_H

#include "app/client_manager.h"

/**
 * @brief Sends a received message to all other connected clients.
 *
 * @param buffer The message buffer to send.
 * @param socketFD The file descriptor of the sender's socket.
 * @param acceptedSockets Array of accepted client connections.
 * @param acceptedSocketsCount Number of currently accepted clients.
 */
void sendReceivedMessageToOtherClients(char *buffer, int socketFD,
                                       Client clients[MAX_CLIENTS],
                                       int acceptedSocketsCount);
/**
 * @brief Thread function that listens for incoming messages and prints them.
 *
 * @param arg Pointer to an integer socket file descriptor (allocated on heap).
 * @return Always returns NULL.
 */
void readAndSendLine(int socketFD);

/**
 * @brief Reads user input from stdin and sends it to the given socket.
 *
 * Prompts the user for their name and continuously sends typed messages
 * to the server. Typing "exit" will terminate the loop.
 *
 * @param socketFD The socket file descriptor to send messages to.
 */
void *listenAndPrint(void *socketFD);

#endif
