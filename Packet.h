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
      Packet(size_t len, uint64_t id);
      virtual ~Packet() = 0;
      void SetPacketByte(size_t pos, uint8_t byte);
      size_t GetPacketLen(void);
      uint64_t GetPacketId(void);

    private:
      std::unique_ptr<uint8_t []> _pkt;
      size_t _pktLen;
      uint64_t _pktId;
  };
}

#endif //__Packet_h
