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

bool Connection::is_connected() {
  if (!this->_is_connected) return _is_connected;

  int error_code = 0;
  socklen_t error_code_size = sizeof(error_code);
  getsockopt(this->socket, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);
  return error_code == 0;
}

void Connection::listen() {
  if (this->debug) std::cout << "\033[32mconnection opened\033[0m" << std::endl;
  this->on_connection(this);
  this->listen_for_message();
  this->_is_connected = false;
  this->on_close();
  if (this->debug) std::cout << "\033[91mconnection closed\033[0m" << std::endl;
}

void Connection::listen_for_message(void) {
  while(this->is_connected()) {
    try {
      Frame frame = read_frame();
      if (this->debug) std::cout << "\033[93m" << frame.to_string() << "\033[0m" << std::endl;
      this->on_message(frame.get_payload());
    } catch (const char * error) {
      std::cout << "\e[91m" << error << "\e[0m" << std::endl;
      break;
    }
  }
}

Frame Connection::read_frame() {
  int size = 512; // @todo calculate this number for better performance and bigger frames
  uint8_t result[size];
  bzero(result, sizeof(result));

  read(socket, result, sizeof(result));

  Frame frame = Frame(result, sizeof(result));
  if (frame.is_empty()) throw "empty_frame";
  
  return frame;
}

void Connection::write(std::string message) {
  Frame frame(message);
  write(&frame.get_data()[0], frame.get_data().size());
}

void Connection::write(uint8_t * buffer, int size) {
  if (this->is_connected()) ::write(socket, buffer, size);
}