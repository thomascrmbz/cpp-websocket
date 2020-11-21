#include "websocket_client.h"

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace WebSocket;

Client::Client(std::string url) {
  int port = 3000;
  struct hostent * host = gethostbyname(url.c_str());

  if ((host == NULL) || (host->h_addr == NULL)) {
    perror("Error retrieving DNS information");
    exit(1);
  }

  this->address.sin_family = AF_INET;
  this->address.sin_port = htons(port);
  memcpy(&this->address.sin_addr, host->h_addr, host->h_length);

  this->socket = ::socket(AF_INET, SOCK_STREAM, 0);

  if (socket < 0) {
    perror("Error creating socket");
    exit(1);
  }
}

void Client::connect(void) {
  if (::connect(this->socket, (struct sockaddr *)&this->address, sizeof(this->address)) < 0 ) {
    close(this->socket);
    perror("Could not connect to server");
    exit(1);
  }

  std::string request = "GET / HTTP/1.1\r\n\r\nHallo\r\n"; // @todo fix sigmentation fault in HTTP lib when sending a request without \r

  if (send(this->socket, request.c_str(), request.length(), 0) != (int) request.length()) {
    perror("Error sending request");
    exit(1);
  }

  uint8_t response[512];
  bzero(response, sizeof(response));
  read(this->socket, response, sizeof(response));
  // @todo check if response is correct

  Connection connection(this->socket, this->on_connection);
  connection.listen();
}