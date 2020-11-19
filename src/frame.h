#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace WebSocket {
  class Frame {

    public:
      Frame(uint8_t data[], int size);

    public:
      std::string to_string(void) const;
      std::string get_payload(void) const;
      bool is_empty(void) const;

    private:
      bool fin;
      int opcode;
      int payload_size;
      int header_size;
      std::vector<uint8_t> data;

  };
}
