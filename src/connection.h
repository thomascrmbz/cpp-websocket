#pragma once

#include <string>
#include <functional>

namespace WebSocket {

  class Connection {

    public:
      Connection(int socket);

    public:
      void listen();

    private:
      std::string read(void) const;
      void write(uint8_t * buffer, int size) const;

    private:
      int socket;

  };
}