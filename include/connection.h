#ifndef CONNECTION_H
#define CONNECTION_H

#include <netinet/in.h>
#include <stdbool.h>

/**
 * @brief Holds information about an accepted client connection.
 */
struct AcceptedSocket {
  int acceptedSocketFD;       /**< Address information of the client. */
  struct sockaddr_in address; /**< File descriptor of the accepted socket. */
  int error;                  /**< Error code if connection failed. */
  bool acceptedSuccessfull;   /**< Whether the connection was accepted
                                 successfully. */
};

/**
 * @brief Creates a configured IPv4 address struct.
 *
 * @param ip The IP address as a string. Use an empty string ("") for
 * INADDR_ANY.
 * @param port The port number to bind or connect to.
 * @return sockaddr_in struct containing connection info
 * */
struct sockaddr_in createTCPIpv4Address(char *ip, int port);

/**
 * @brief Creates an IPv4 TCP socket.
 *
 * @return A socket file descriptor, or -1 on error.
 */
int createTCPIpv4Socket();

/**
 * @brief Accepts an incoming TCP connection on the given socket.
 *
 * @param serverSocketFD File descriptor of the listening socket.
 * @return An AcceptedSocket struct containing the client connection details.
 */
struct AcceptedSocket acceptIncomingConnection(int serverSocketFD);

#endif
