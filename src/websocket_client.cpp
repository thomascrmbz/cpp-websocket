#include "websocket_client.h"

#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace WebSocket;

Client::Client(std::string url) {
  int socket;
  struct sockaddr_in client;
  int PORT = 3000;
  struct hostent * host = gethostbyname("127.0.0.1");

  if ((host == NULL) || (host->h_addr == NULL)) {
    std::cout << "Error retrieving DNS information" << std::endl;
    exit(1);
  }

  bzero(&client, sizeof(client));
  client.sin_family = AF_INET;
  client.sin_port = htons(PORT);

  memcpy(&client.sin_addr, host->h_addr, host->h_length);

  socket = ::socket(AF_INET, SOCK_STREAM, 0);

  if (socket < 0) {
    std::cout << "Error creating socket" << std::endl;
    exit(1);
  }

  if (::connect(socket, (struct sockaddr *)&client, sizeof(client)) < 0 ) {
    close(socket);
    std::cout << "Could not connect" << std::endl;
    exit(1);
  }

  std::string request = "GET / HTTP/1.1\r\n\r\nHallo\r\n"; // @todo fix sigmentation fault in HTTP lib when sending a request without \r
  
  if (send(socket, request.c_str(), request.length(), 0) != (int)request.length()) {
    std::cout << "Error sending request" << std::endl;
    exit(1);
  }

  uint8_t result[512];
  bzero(result, sizeof(result));
  read(socket, result, sizeof(result));
  // @todo check if response is correct
  
  while(true) {
    bzero(result, sizeof(result));
    read(socket, result, sizeof(result));

    std::cout << "received: ";
    for (int i = 2; i < sizeof(result); i++) std::cout << result[i];
    std::cout << std::endl;

    uint8_t buffer[] = { 0x81, 0x0C, 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
    send(socket, buffer, sizeof(buffer), 0);
    sleep(1);
  }
  
}