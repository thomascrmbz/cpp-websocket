#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace WebSocket {
  class Frame {

    public:
      Frame(uint8_t buffer[], int size);
      // Frame(uint8_t buffer[], int size, bool includes_header);
      Frame(std::string message);

    public:
      std::string get_payload(void) const;
      int get_header_size(void) const;
      int get_payload_size(void) const;
      std::vector<uint8_t> get_data(void) const;

      int get_opcode(void) const;

    public:
      void set_opcode(int code);

    public:
      std::string to_string(void) const;
      bool is_empty(void) const;

    private:
      void create_frame(std::vector<uint8_t> data);
      void create_frame_from_payload(std::vector<uint8_t> payload);

    private:
      bool fin;
      int opcode;
      int mask;
      int payload_size;
      int header_size;
      std::vector<uint8_t> data;

  };
}
