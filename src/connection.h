#pragma once

#include <string>
#include <functional>

namespace WebSocket {

  class Connection {

    public:
      Connection(int socket);

    public:
      void listen();
      void write(uint8_t * buffer, int size) const;

    public:
      void set_on_connection_callback(std::function<void(WebSocket::Connection *)> callback);
      void set_on_message_callback(std::function<void(std::string, WebSocket::Connection *)> callback);

    private:
      void listen_for_message(void);

    private:
      int socket;
      std::function<void(WebSocket::Connection *)> on_connection_callback;
      std::function<void(std::string, WebSocket::Connection *)> on_message_callback;

  };
}