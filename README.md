# C++ WebSocket

A C++ WebSocket library

# Getting Started

```c++
#include <websocket_client.h>

int main() {

  WebSocket::Client client("localhost");

  client.on_connection = [&](WebSocket::Connection * connection) {
    connection->write("Hello World!");

    connection->on_message = [connection](std::string message) {
      std::cout << message << std::endl;
    };
  };

  client.connect();

  return 0;
}
```

# License

This project is licensed under the MIT License.