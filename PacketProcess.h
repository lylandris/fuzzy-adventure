#ifndef __PacketProcess_h
#define __PacketProcess_h

#include <mutex>

#include "Packet.h"
#include "Process.h"

namespace ctc
{
  class PacketProcess : virtual public Packet, virtual public Process
  {
    public:
      PacketProcess(uint64_t id, size_t len, uint64_t startTick);
      virtual ~PacketProcess(void);
    private:
      static void PrintStatus(PacketProcess& theProc);
      static void PerformProcessing(PacketProcess& theProc);
      static std::mutex _m;
  };
}

#endif //__PacketProcess_h
