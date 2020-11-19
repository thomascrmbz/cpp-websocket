#include "connection.h"

#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/socket.h>

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

    if (error_code) break;

    try {
        Frame frame = read_frame();
        if (this->debug) std::cout << "\033[93m" << frame.to_string() << "\033[0m" << std::endl;
        this->on_message(frame.get_payload());
    } catch (const char * error) {
      break;
    }
  }
}

Frame Connection::read_frame() {
  int size = 192; // @todo calculate this number for better performance
  uint8_t result[size];
  bzero(result, sizeof(result));

  read(socket, result, sizeof(result));

  Frame frame = Frame(result, sizeof(result));
  if (frame.is_empty()) throw "empty_frame";
  
  return frame;
}

void Connection::write(uint8_t * buffer, int size) const {
  int error_code = 0;
  socklen_t error_code_size = sizeof(error_code);
  getsockopt(socket, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);
  if (error_code == 0) {
    ::write(socket, buffer, size);
  }
}