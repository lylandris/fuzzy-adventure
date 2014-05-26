#include <cstdint>
#include <iostream>
#include <functional>
#include <thread>
#include <vector>
#include <memory>

#include "PacketProcess.h"

using namespace ctc;

static void PacketGenerator(std::vector<std::unique_ptr<PacketProcess>> &packets)
{
  const uint64_t MAX_PACKET_ID = 100;
  const size_t pktSizeList[] = {64, 1518, 256, 9600};

  std::cout << "Start to send packets ..." << std::endl;
  for (uint64_t id = 0; id < MAX_PACKET_ID; id++)
  {
    size_t pktLen = pktSizeList[id % 4];
    std::unique_ptr<PacketProcess> pkt(new PacketProcess(id, pktLen));
    packets.push_back(std::move(pkt));
  }
}

int main(int argc, char** argv)
{
  std::unique_ptr<std::vector<std::unique_ptr<PacketProcess>>> active(new std::vector<std::unique_ptr<PacketProcess>>);
  std::unique_ptr<std::vector<std::unique_ptr<PacketProcess>>> backup(new std::vector<std::unique_ptr<PacketProcess>>);
  std::vector<std::thread> eventList;

  PacketGenerator(*active);

  uint64_t globalTick = 0;
  while (true)
  {
    if (active->empty() && backup->empty()) break;

    for (auto& x: (*active))
    {
      if (x->DesireRun(globalTick))
      {
        eventList.push_back(std::thread(Process::Notify, std::ref(*x), globalTick));
      }
    }

    for (auto& e: eventList)
    {
      e.join();
    }

    eventList.clear();
    globalTick++;

    if (0 != globalTick % 50) continue;

    //std::cerr << '.';
    for (auto& x: (*active))
    {
      if (!x->IsFinished())
      {
        backup->push_back(std::move(x));
      }
    }

    active->clear();
    std::swap(active, backup);
  }

  std::cout << "It works!" << std::endl;

  return 0;
}
