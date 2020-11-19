#pragma once

#include <string>

#include <http.h>
#include "connection.h"

namespace WebSocket {
  class Server {

    public:
      Server(void);

    public:
      void listen(int port);

    public:
      std::function<void(WebSocket::Connection *)> on_connection = [](WebSocket::Connection * connection) {};
      std::function<void(std::string, WebSocket::Connection *)> on_message = [](std::string message, WebSocket::Connection * connection) {};
      // std::function<void()> on_close = []() {};

  };
}
