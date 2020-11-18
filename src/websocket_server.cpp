#include "websocket_server.h"

#include <iostream>
#include <algorithm>
#include <future>
#include <thread>
#include <unistd.h>
#include <sys/socket.h>

#include "frame.h"
#include "lib/base64.h"
#include "lib/sha1.h"

using namespace WebSocket;

Server::Server(void) {

}

std::vector<uint8_t> string_to_bytes(std::string s) {
  std::vector<uint8_t> result;
  for (int i = 0; i < s.size(); i+=2) result.push_back(std::stoi(s.substr(i, 2), 0, 16));
  return result;
}

void Server::listen(int port) const {
  std::cout << "listening on port " << port << " in thread " << std::this_thread::get_id() << std::endl;

  HTTP::Server server;

  server.handle = [](HTTP::Request req, HTTP::Response res) {
    std::cout << "new connection incomming..." << std::endl;

    res.set_status("101 Switching Protocols");
    std::vector<HTTP::Header> headers = {
      HTTP::Header("Connection", "Upgrade"),
      HTTP::Header("Upgrade", "websocket"),
      HTTP::Header("Sec-WebSocket-Accept", Base64::Encode(string_to_bytes(sha1(req.get_header("Sec-WebSocket-Key").get_value() + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11")))),
    };
    res.set_headers(headers);
    res.set_content("");
    res.send();

    std::thread th(&Server::listen_socket, res._get_socket());
    th.detach();
  };

  server.listen(port);
}

void Server::listen_socket(int socket) {
  std::cout << "listening on socket " << socket << " in thread " << std::this_thread::get_id() << std::endl;

  int error_code = 0;
  bool disconnected = false;
  int looped = 0;

  while (!error_code && !disconnected) {
    uint32_t buffer[1024];
    bzero(buffer, 1024);

    std::cout << "buffer reading on socket " << socket << " in thread " << std::this_thread::get_id() << std::endl;
    read(socket, buffer, 1024); // @todo buffer is not clearing after first loop??
    Frame frame = Frame(buffer);

    // @todo fix error: A server must not mask any frames that it sends to the client.
    if (looped == 0) {  // (reply frame is response frame after first loop???)
      uint32_t reply[1024] = { 0x65480581, 0x006f6c6c }; // frame with content "Hello"
      Frame f = Frame(reply);
      write(socket, reply, sizeof(reply));
      std::cout << "frame send back on socket " << socket << " in thread " << std::this_thread::get_id() << std::endl;
    }

    socklen_t error_code_size = sizeof(error_code);
    getsockopt(socket, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);

    std::cout << "done with request on socket " << socket << " in thread " << std::this_thread::get_id() << std::endl;
    looped++;
    bzero(buffer, 1024); // not working?
  }

  std::cout << "socket " << socket << " closed in thread " << std::this_thread::get_id() << std::endl;
  close(socket);
}