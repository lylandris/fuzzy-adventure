#include <cstdint>
#include <iostream>
#include <functional>
#include <thread>
#include <vector>
#include <memory>
#include <forward_list>

#include "PacketProcess.h"

using namespace ctc;

const uint64_t MAX_PACKET_ID = 10;
const size_t pktSizeList[] = {64, 1518, 256, 9600};

int main(int argc, char** argv)
{
  std::forward_list<std::unique_ptr<PacketProcess>> packets;
  std::forward_list<std::thread> eventList;

  uint64_t globalTick = 0;
  while (true)
  {
    if (globalTick < 1000)
    {
      size_t pktLen = pktSizeList[globalTick % 4];
      std::unique_ptr<PacketProcess> pkt(new PacketProcess(globalTick, pktLen, globalTick));
      packets.push_front(std::move(pkt));
    }

    if (packets.empty()) break;

    for (auto& x: packets)
    {
      if (x->DesireRun(globalTick))
      {
        eventList.push_front(std::thread(Process::Notify, std::ref(*x), globalTick));
      }
    }

    for (auto& e: eventList)
    {
      e.join();
    }

    eventList.clear();
    globalTick++;

    if (0 != globalTick % 50) continue;
    packets.remove_if([](const std::unique_ptr<PacketProcess> &p){ return p->IsFinished();});
  }

  std::cout << "It works!" << std::endl;

  return 0;
}
