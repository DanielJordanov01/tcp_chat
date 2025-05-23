#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include "client_manager.h"
void runServerLoop(ClientManager *manager, int serverSocketFD);

#endif
