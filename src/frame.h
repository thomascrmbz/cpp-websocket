#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace WebSocket {
  class Frame {

    public:
      Frame(uint8_t data[], int size);

    public:
      std::string get_payload(void) const;
      int get_header_size(void) const;
      int get_payload_size(void) const;

    public:
      std::string to_string(void) const;
      bool is_empty(void) const;

    private:
      bool fin;
      int opcode;
      int mask;
      int payload_size;
      int header_size;
      std::vector<uint8_t> data;

  };
}
