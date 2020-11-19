#include <websocket_server.h>

#include <string>
#include <iostream>

int main() {

  WebSocket::Server server;

  server.on_message = [](std::string message, const WebSocket::Connection * connection) {
    std::cout << message << std::endl;
    uint8_t buffer[] = { 0x81, 0x0C, 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
    connection->write(buffer, sizeof(buffer));
  };

  server.listen(3000);

  return 0;
}