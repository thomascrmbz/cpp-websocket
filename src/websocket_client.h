#pragma once

#include <http.h>

#include <string>
#include <functional>

namespace WebSocket {
  class Client {

    public:
      Client(std::string url);

    public:
      std::function<void()> on_open = []() {};
      std::function<void(std::string)> message = [](std::string message) {};

    public:
      void connect(void);

  };
}
