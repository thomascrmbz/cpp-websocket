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

void Connection::listen() {
  std::cout << "listening on socket " << this->socket << " in thread " << std::this_thread::get_id() << std::endl;
  this->on_connection(this);
  this->listen_for_message();
  std::cout << "client disconnected" << std::endl;
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
        std::cout << frame.to_string() << std::endl;
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
    std::cout << "sending frame to socket " << this->socket << " in thread " << std::this_thread::get_id() << std::endl;
  }
}