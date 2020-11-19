#include <websocket_server.h>

#include <string>
#include <iostream>

int main() {

  WebSocket::Server server;

  server.on_message = [](std::string message) {
    std::cout << message << std::endl;
  };

  server.listen(3000);

  return 0;
}