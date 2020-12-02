#pragma once

#include <string>
#include <functional>

#include "frame.h"

namespace WebSocket {

  class Connection {

    public:
      Connection(int socket, std::function<void(WebSocket::Connection *)> callback);

    public:
      void set_debug(bool value);
      bool is_connected();

    public:
      void listen();
      void write(std::string message);
      void write(uint8_t * buffer, int size);

    public:
      std::function<void(WebSocket::Frame)> on_message = [](WebSocket::Frame frame) {};
      std::function<void()> on_close = []() {};

    private:
      void listen_for_message(void);
      WebSocket::Frame read_frame();

    private:
      int socket;
      bool debug;
      std::function<void(WebSocket::Connection *)> on_connection;
      bool _is_connected = true;

  };
}