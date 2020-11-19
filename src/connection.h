#pragma once

#include <string>
#include <functional>

namespace WebSocket {

  class Connection {

    public:
      Connection(int socket, std::function<void(WebSocket::Connection *)> callback);

    public:
      void listen();
      void write(uint8_t * buffer, int size) const;

    public:
      std::function<void(std::string)> on_message = [](std::string message) {};

    private:
      void listen_for_message(void);

    private:
      int socket;
      std::function<void(WebSocket::Connection *)> on_connection;

  };
}