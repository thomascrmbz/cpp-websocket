#include "connection.h"

#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/socket.h>

#include "frame.h"

using namespace WebSocket;

Connection::Connection(int socket, std::function<void(WebSocket::Connection *)> callback) {
  this->socket = socket;
  this->on_connection = callback;
}

void Connection::set_debug(bool value) {
  this->debug = value;
}

void Connection::listen() {
  std::cout << "\033[32mclient connected\033[0m" << std::endl;
  this->on_connection(this);
  this->listen_for_message();
  std::cout << "\033[91mclient disconnected\033[0m" << std::endl;
}

void Connection::listen_for_message(void) {
  int error_code = 0;
  while (error_code == 0) {
    socklen_t error_code_size = sizeof(error_code);
    getsockopt(this->socket, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);
    if (error_code == 0) {
      uint8_t min_header[2];
      bzero(min_header, 2);
      ::read(this->socket, min_header, sizeof(min_header));
      if (min_header[0] != 0x00 && min_header[1] != 0x00) {
        Frame frame = Frame(min_header, this->socket);
        if (this->debug) std::cout << "received: \033[93m" << frame.to_string() << "\033[0m" << std::endl;
        this->on_message(frame.get_payload());
      } else break;
    }
  }
}

void Connection::write(uint8_t * buffer, int size) const {
  int error_code = 0;
  socklen_t error_code_size = sizeof(error_code);
  getsockopt(socket, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);
  if (error_code == 0) {
    ::write(socket, buffer, size);
  }
}