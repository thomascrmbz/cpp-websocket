#pragma once

#include <string>

namespace WebSocket {

  class Connection {

    public:
      Connection(int socket);

    public:
      void listen();
      std::string read(void) const;
      void write(uint8_t * buffer, int size) const;

    private:
      int socket;

  };
}