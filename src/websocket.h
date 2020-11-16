#pragma once

namespace WebSocket {
  class Server {

    public:
      Server(void);

    public:
      void listen(int port) const;

  };
}
