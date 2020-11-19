#pragma once

#include <string>
#include <functional>

#include "websocket_server.h"

namespace WebSocket {

  class Connection {

    public:
      Connection(const WebSocket::Server * server, int socket);

    public:
      void listen();

    private:
      void listen_for_message(void) const;
      void write(uint8_t * buffer, int size) const;

    private:
      int socket;
      const WebSocket::Server * server;

  };
}