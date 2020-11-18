#pragma once

#include <iostream>
#include <string>

namespace WebSocket {
  class Frame {

    public:
      Frame(uint8_t min_header[2], int socket);

    public:
      std::string to_string(void) const;
      std::string get_payload(void) const;

    private:
      bool fin;
      int opcode;
      int payload_lenght;
      uint8_t * data;
      std::string frame_string;
      std::string payload_string;

  };
}
