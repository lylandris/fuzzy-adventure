#include "Packet.h"

using namespace ctc;

Packet::Packet(size_t len)
{
  _pktLen = len;
  _pkt = std::unique_ptr<uint8_t []>(new uint8_t[len]);
}

Packet::~Packet()
{
}

void Packet::SetPacketByte(size_t pos, uint8_t byte)
{
  if (0 <= pos && pos < _pktLen)
  {
    _pkt[pos] = byte;
  }
}

size_t Packet::GetPacketLen(void)
{
  return _pktLen;
}
