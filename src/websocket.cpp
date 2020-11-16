#include <iostream>

#include "websocket.h"

using namespace WebSocket;

Server::Server(void) {

}

void Server::listen(int port) const {
  std::cout << "listening on port " << port << std::endl;
}