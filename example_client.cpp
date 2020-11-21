#include <websocket_client.h>

#include <iostream>
#include <unistd.h>

int main() {

  WebSocket::Client client("localhost");

  client.on_connection = [&](WebSocket::Connection * connection) {
    uint8_t buffer[] = { 0x81, 0x0C, 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
    connection->write(buffer, sizeof(buffer));

    connection->on_message = [connection](std::string message) {
      std::cout << message << std::endl;
      sleep(1);
      uint8_t buffer[] = { 0x81, 0x04, 'p', 'i', 'n', 'g' };
      connection->write(buffer, sizeof(buffer));
    };
  };

  client.connect();

  return 0;
}