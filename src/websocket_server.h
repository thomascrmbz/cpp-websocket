#pragma once

#include <string>

#include <http.h>

namespace WebSocket {
  class Server {

    public:
      Server(void);

    public:
      void listen(int port) const;

    public:
      std::function<void()> on_open = []() {};
      std::function<void(std::string)> on_message = [](std::string message) {};
      std::function<void()> on_close = []() {};

  };
}
