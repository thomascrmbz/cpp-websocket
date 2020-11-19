#include "frame.h"

#include <sstream>

using namespace WebSocket;

Frame::Frame(uint8_t data[], int size) {
  for (int i = 0; i < size; i++) this->data.push_back(data[i]);

  this->fin = (this->data[0] & 0x80) == 0x80;
  this->opcode = this->data[0] & 0x0F;
  this->mask = (this->data[1] & 0x80) == 0x80;

  if (this->data[1] == 0x7F) {
    // 7+64 bit
    this->header_size = 8;

    std::cout << "\e[91payload over 8388607 bits are not yet supported!\e[0m" << std::endl;
    this->payload_size = 0;
  }
  else if (this->data[1] == 0x7E) {
    // 7+16 bit
    this->header_size = 4;

    this->payload_size = this->data[2] << 8 | this->data[3];
  }
  else {
    this->payload_size = this->data[1] & 0x7F;
    this->header_size = 2;
  }

  if (this->mask) std::cout << "\e[91mmasked frames are not yet supported!\e[0m" << std::endl;
}

std::string Frame::to_string(void) const {
  std::stringstream ss;
  for (int i = 0; i < this->payload_size + this->header_size; i++) ss << "0x" << std::hex << (int) this->data[i] << std::dec << " ";
  return ss.str();
}

std::string Frame::get_payload(void) const {
  return std::string(this->data.begin() + this->header_size, this->data.end());
}

bool Frame::is_empty(void) const {
  return this->data[0] == 0x00 || this->data[1] == 0x00;
}

int Frame::get_header_size(void) const {
  return this->header_size;
}

int Frame::get_payload_size(void) const {
  return this->payload_size;
}