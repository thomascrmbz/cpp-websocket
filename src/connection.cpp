#include "connection.h"

#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/socket.h>

#include "frame.h"

using namespace WebSocket;

Connection::Connection(int socket) {
  this->socket = socket;
}

void Connection::listen() {
  std::cout << "listening on socket " << this->socket << " in thread " << std::this_thread::get_id() << std::endl;

  uint8_t buffer[] = { 0x81, 0x0C, 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!' };

  int error_code = 0;
  while (!error_code) {
    socklen_t error_code_size = sizeof(error_code);
    getsockopt(socket, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);
    if (!error_code) write(buffer, sizeof(buffer));
    std::this_thread::sleep_for((std::chrono::seconds) 2);
  }
  std::cout << "client disconnected" << std::endl;
}

std::string Connection::read(void) const {
  std::this_thread::sleep_for((std::chrono::seconds) 2);
  return "default message";
}

void Connection::write(uint8_t * buffer, int size) const {
  ::write(socket, buffer, size);
  std::cout << "sending frame to socket " << this->socket << " in thread " << std::this_thread::get_id() << std::endl;
}