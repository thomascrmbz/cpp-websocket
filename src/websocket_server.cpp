#include "websocket_server.h"

#include <iostream>

using namespace WebSocket;

Server::Server(void) {

}

void Server::listen(int port) const {
  std::cout << "listening on port " << port << std::endl;

  HTTP::Server server = HTTP::Server(false);

  server.handle = [](HTTP::Request req, HTTP::Response res) {
    res.set_content("C++ WebSocket");
    res.send();
  };

  server.listen(port);
}