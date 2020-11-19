#pragma once

#include <string>
#include <functional>

namespace WebSocket {

  class Connection {

    public:
      Connection(int socket, std::function<void(std::string, const WebSocket::Connection *)> on_message);

    public:
      void listen();
      void write(uint8_t * buffer, int size) const;

    private:
      void listen_for_message(void) const;

    private:
      int socket;
      std::function<void(std::string, const WebSocket::Connection *)> on_message;

  };
}