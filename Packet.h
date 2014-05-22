#ifndef __Packet_hpp
#define __Packet_hpp

#include <cstdint>
#include <memory>

#include "Object.h"

namespace ctc
{
  class Packet : virtual public Object
  {
    public:
      Packet(size_t len);
      virtual ~Packet() = 0;
      void SetPacketByte(size_t pos, uint8_t byte);
      size_t GetPacketLen(void);

    private:
      std::unique_ptr<uint8_t []> _pkt;
      size_t _pktLen;
  };
}

#endif //__Packet_hpp
