#ifndef __PacketProcess_h
#define __PacketProcess_h

#include "Packet.h"
#include "Process.h"

namespace ctc
{
  class PacketProcess : virtual public Packet, virtual public Process
  {
    public:
      PacketProcess(size_t len, uint64_t id);
      virtual ~PacketProcess(void);
    private:
      static void PerformProcessing(PacketProcess& theProc);
  };
}

#endif //__PacketProcess_h
