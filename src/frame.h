#pragma once

#include <iostream>

namespace WebSocket {
  class Frame {

    public:
      Frame(uint32_t buffer[1024]);

    private:
      uint32_t reverse_bits(uint32_t n);
      bool fin;

  };
}
