#pragma once

#include <string>

#include <http.h>
#include "connection.h"

namespace WebSocket {
  class Server {

    public:
      Server(void);

    public:
      void listen(int port) const;

    public:
      std::function<void(const WebSocket::Connection *)> on_connection = [](const WebSocket::Connection * connection) {};
      std::function<void(std::string, const WebSocket::Connection *)> on_message = [](std::string message, const WebSocket::Connection * connection) {};
      // std::function<void()> on_close = []() {};

  };
}
