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
#include "connection.h"

using namespace WebSocket;

Server::Server(void) {

}

void Server::set_debug(bool value) {
  this->debug = value;
}

std::vector<uint8_t> string_to_bytes(std::string s) {
  std::vector<uint8_t> result;
  for (int i = 0; i < s.size(); i+=2) result.push_back(std::stoi(s.substr(i, 2), 0, 16));
  return result;
}

void Server::listen(int port) {
  if (this->debug) std::cout << "listening on port " << port << " in thread " << std::this_thread::get_id() << std::endl;

  HTTP::Server server;

  server.handle = [&](HTTP::Request req, HTTP::Response res) {
    res.set_status("101 Switching Protocols");
    std::vector<HTTP::Header> headers = {
      HTTP::Header("Connection", "Upgrade"),
      HTTP::Header("Upgrade", "websocket"),
      HTTP::Header("Sec-WebSocket-Accept", Base64::Encode(string_to_bytes(sha1(req.get_header("Sec-WebSocket-Key").get_value() + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11")))),
    };
    res.set_headers(headers);
    res.set_content("");
    res.send();

    Connection connection(res._get_socket(), this->on_connection);
    connection.set_debug(this->debug);

    std::thread th(&Connection::listen, connection);
    th.detach();
  };

  server.listen(port);
}