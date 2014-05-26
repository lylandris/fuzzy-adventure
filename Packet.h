#ifndef __Packet_h
#define __Packet_h

#include <cstdint>
#include <memory>

#include "Object.h"

namespace ctc
{
  class Packet : virtual public Object
  {
    public:
      Packet(uint64_t id, size_t len);
      virtual ~Packet() = 0;
      void SetPacketByte(size_t pos, uint8_t byte);
      size_t GetPacketLen(void) const;
      uint64_t GetPacketId(void) const;

    private:
      const uint64_t _pktId;
      const size_t _pktLen;
      std::unique_ptr<uint8_t []> _pkt;
  };
}

#endif //__Packet_h
