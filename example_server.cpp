#include <websocket_server.h>

#include <string>
#include <iostream>

int main() {

  WebSocket::Server server;

  server.on_message = [](std::string message, WebSocket::Connection * connection) {
    std::cout << message << std::endl;
    uint8_t buffer[] = { 0x81, 0x0D, 'D', 'e', 'f', 'a', 'u', 'l', 't', ' ', 'r', 'e', 'p', 'l', 'y' };
    connection->write(buffer, sizeof(buffer));
  };

  server.on_connection = [](WebSocket::Connection * connection) {
    std::cout << "new connection" << std::endl;

    uint8_t buffer[] = { 0x81, 0x0C, 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
    connection->write(buffer, sizeof(buffer));

    // connection->on_message = [](std::string message) {};
  };

  server.listen(3000);

  return 0;
}