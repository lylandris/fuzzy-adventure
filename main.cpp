#include <cstdint>
#include <iostream>
#include <functional>
#include <thread>
#include <vector>
#include <memory>

#include "SafeQueue.h"

using namespace ctc;

static const size_t FIFO_DEPTH = 1;
static SafeQueue<int> fifo(FIFO_DEPTH);

static const size_t TRIGGER_FIFO_DEPTH = 100;
static SafeQueue<uint64_t> trigger(TRIGGER_FIFO_DEPTH);

struct RunningFlag
{
  bool waiting;
  bool done;
};

class PacketProcess
{
  private:
    int32_t _packetId;
    uint64_t _tick;
#if 0
    static void CheckProcAndWait(PacketProcess& pkt, SafeQueue<int> &fifo, SafeQueue<uint64_t> trigger, uint64_t delay)
    {
      while (pkt._tick + delay < trigger.DeQueue())
      {
        fifo.EnQueue(pkt._packetId);
      }

      pkt._tick += delay;
    }
#endif

  public:
    PacketProcess(int32_t id)
    {
      _packetId = id;
      _tick = 10 + _packetId;
    }

    virtual ~PacketProcess(void)
    {
    }

    int32_t GetPacketId(void) const
    {
      return _packetId;
    }

    uint64_t GetTick(void) const
    {
      return _tick;
    }

    void MoveNextTick(uint64_t delay)
    {
      _tick += delay;
    }

    static void PktProc(std::unique_ptr<PacketProcess> pkt, SafeQueue<int> &fifo, SafeQueue<uint64_t> &trigger)
    {
      uint64_t delay = 20;
      int32_t pktId = pkt->GetPacketId();

      {
        uint64_t theNextTick = pkt->GetTick() + delay;
        while (true)
        {
          uint64_t globalTick = trigger.DeQueue();
          if (globalTick < theNextTick)
          {
            //std::cout << "[Step 1] Packet_" << pktId << " is waiting @ " << globalTick << "..." << std::endl;
            fifo.EnQueue(pktId);
          }
          else
          {
            pkt->MoveNextTick(delay);
            fifo.EnQueue(pktId);
            break;
          }
        }

        std::cout << "[Step 1] Packet_" << pktId << " is processing @ " << theNextTick << "..." << std::endl;
      }

      {
        uint64_t theNextTick = pkt->GetTick() + delay;
        while (true)
        {
          uint64_t globalTick = trigger.DeQueue();
          if (globalTick < theNextTick)
          {
            //std::cout << "[Step 2] Packet_" << pktId << " is waiting @ " << globalTick << "..." << std::endl;
            fifo.EnQueue(pktId);
          }
          else
          {
            pkt->MoveNextTick(delay);
            fifo.EnQueue(pktId);
            break;
          }
        }

        std::cout << "[Step 2] Packet_" << pktId << " is processing @ " << theNextTick << "..." << std::endl;
      }

      {
        uint64_t theNextTick = pkt->GetTick() + delay;
        while (true)
        {
          uint64_t globalTick = trigger.DeQueue();
          if (globalTick < theNextTick)
          {
            //std::cout << "[Step 3] Packet_" << pktId << " is waiting @ " << globalTick << "..." << std::endl;
            fifo.EnQueue(pktId);
          }
          else
          {
            pkt->MoveNextTick(delay);
            fifo.EnQueue(pktId);
            break;
          }
        }

        std::cout << "[Step 3] Packet_" << pktId << " is processing @ " << theNextTick << "..." << std::endl;
      }

      while (true)
      {
        trigger.DeQueue();
        fifo.EnQueue(pktId);
      }

#if 0
      CheckProcAndWait(*pkt, fifo, trigger, delay);
      std::cout << "Packet " << pkt->GetPacketId() << " is processing ... <STEP 1>" << std::endl;

      CheckProcAndWait(*pkt, fifo, trigger, delay);
      std::cout << "Packet " << pkt->GetPacketId() << " is processing ... <STEP 2>" << std::endl;

      CheckProcAndWait(*pkt, fifo, trigger, delay);
      std::cout << "Packet " << pkt->GetPacketId() << " is processing ... <STEP 3>" << std::endl;

      CheckProcAndWait(*pkt, fifo, trigger, delay);
      std::cout << "Packet " << pkt->GetPacketId() << " is processing ... <STEP 4>" << std::endl;
#endif
    }
};

int main(int argc, char** argv)
{
  const uint32_t total = 20;
  std::vector<std::unique_ptr<std::thread>> packets;

  std::cout << "Start to send packets ..." << std::endl;
  for (uint32_t id = 0; id < total; id++)
  {
    std::unique_ptr<PacketProcess> pkt(new PacketProcess(id));
    std::unique_ptr<std::thread> p(new std::thread(PacketProcess::PktProc, std::move(pkt), std::ref(fifo), std::ref(trigger)));
    packets.push_back(std::move(p));
  }

  uint64_t globalTick = 0;
  while (true)
  {
    for (auto& x: packets)
    {
      x->get_id();
      trigger.EnQueue(globalTick);
    }

    for (auto& x: packets)
    {
      x->get_id();
      fifo.DeQueue();
    }

    globalTick++;
    if (globalTick > 10000) break;
    if (0 == globalTick % 100)
    {
      std::cerr << '.';
    }
  }

  for (auto& p:packets)
  {
    p->join();
  }

  std::cout << "It works!" << std::endl;

  return 0;
}
