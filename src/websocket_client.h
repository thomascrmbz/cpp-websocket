#pragma once

#include <http.h>

#include <string>
#include <functional>
#include <netinet/in.h>
#include "connection.h"

namespace WebSocket {
  class Client {

    public:
      Client(std::string url);

    public:
      std::function<void(WebSocket::Connection *)> on_connection = [](WebSocket::Connection * connection) {};

    public:
      void connect(void);

    private:
      void listen_for_message(void);

    private:
      int socket;
      struct sockaddr_in address;
  };
}
