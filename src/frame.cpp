#include "frame.h"

#include <unistd.h>
#include <sstream>

using namespace WebSocket;

Frame::Frame(uint8_t buffer[2], int socket) {
  int size = 2;

  this->fin = (buffer[0] & 0x80) == 0x80;
  this->opcode = buffer[0] & 0x0F;
  this->payload_lenght = buffer[1] & 0x7F;

  uint8_t result[size + payload_lenght];
  bzero(result, size + payload_lenght);
  for (int i = 0; i < size; i++) result[i] = buffer[i];

  uint8_t payload[payload_lenght];
  read(socket, payload, sizeof(payload));
  for (int i = 0; i < sizeof(payload); i++) result[size+i] = payload[i];

  this->data = result;

  std::stringstream ss1;
  std::stringstream ss2;
  for (int i = 0; i < this->payload_lenght + 2; i++) ss1 << "0x" << std::hex << (int) this->data[i] << std::dec << " ";
  for (int i = 0; i < this->payload_lenght; i++) ss2 << this->data[i+2];
  this->frame_string = ss1.str();
  this->payload_string = ss2.str();
}

std::string Frame::to_string(void) const {
  return this->frame_string;
}

std::string Frame::get_payload(void) const {
  return this->payload_string;
}