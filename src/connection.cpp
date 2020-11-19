#include "connection.h"

#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/socket.h>

#include "frame.h"

using namespace WebSocket;

Connection::Connection(const Server * server, int socket) {
  this->socket = socket;
  this->server = server;
}

void Connection::listen() {
  std::cout << "listening on socket " << this->socket << " in thread " << std::this_thread::get_id() << std::endl;

  // uint8_t buffer[] = { 0x81, 0x0C, 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!' };

  // int error_code = 0;

  // while (!error_code) {
  //   socklen_t error_code_size = sizeof(error_code);
  //   getsockopt(socket, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);
  //   if (!error_code) {
  //     std::string message = read();
  //     if (message.length() > 0) std::cout << message << std::endl;
  //     write(buffer, sizeof(buffer));
  //   }
  // }
  // std::cout << "client disconnected" << std::endl;

  this->listen_for_message();
  std::cout << "client disconnected" << std::endl;
}

void Connection::listen_for_message(void) const {
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
        this->server->on_message(frame.get_payload());
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