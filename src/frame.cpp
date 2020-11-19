#include "frame.h"

#include <sstream>

using namespace WebSocket;

Frame::Frame(uint8_t data[], int size) {
  for (int i = 0; i < size; i++) this->data.push_back(data[i]);

  this->fin = (this->data[0] & 0x80) == 0x80;
  this->opcode = this->data[0] & 0x0F;
  this->payload_size = this->data[1] & 0x7F;
  this->header_size = 2; // @todo calculate header_size (payload_size <= 0x7F == 2)
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