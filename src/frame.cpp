#include "frame.h"

using namespace WebSocket;

uint32_t Frame::reverse_bits(uint32_t n) {
  uint32_t ans = 0;
  for(int i = 31; i >= 0; i--){
      ans |= (n & 1) <<i;
      n>>=1;
  }
  return ans;
}

Frame::Frame(uint32_t buffer[1024]) {
  std::cout << "buffer: " << std::hex << buffer << std::dec << std::endl;

  uint32_t bits = reverse_bits(std::bitset<32> (buffer[0]).to_ulong());
  fin = bits >> 31;

  std::cout << "FIN: " << fin << std::endl;

}