#include <cstdint>
#include <iostream>
#include <functional>
#include <thread>
#include <vector>
#include <memory>

#include "PacketProcess.h"

using namespace ctc;

std::vector<std::unique_ptr<PacketProcess>> packetList;
std::vector<std::thread> eventList;
std::vector<std::unique_ptr<std::atomic<bool>>> doneList;

static void PacketGenerator(void)
{
  std::cout << "Start to send packets ..." << std::endl;
  const uint64_t MAX_PACKET_ID = 100;
  const int32_t THE_PACKET_LEN_LIST_SIZE = 4;
  const size_t THE_PACKET_LEN[THE_PACKET_LEN_LIST_SIZE] = {64, 1518, 256, 9600};
  for (uint64_t id = 0; id < MAX_PACKET_ID; id++)
  {
    size_t pktLen = THE_PACKET_LEN[id % THE_PACKET_LEN_LIST_SIZE];
    std::unique_ptr<PacketProcess> pkt(new PacketProcess(id, pktLen));
    packetList.push_back(std::move(pkt));

    //for (size_t i = 0; i < pktLen * 100; i++);
  }
}

int main(int argc, char** argv)
{
  PacketGenerator();
  const uint64_t totalTickStep = 1000;

  uint64_t globalTick = 0;
  while (true)
  {
    for (auto& x: packetList)
    {
      std::unique_ptr<std::atomic<bool>> flag(new std::atomic<bool>(false));
      eventList.push_back(std::thread(Process::Notify, std::ref(*x), std::ref(*flag)));
      doneList.push_back(std::move(flag));
    }

    for (auto& e: eventList)
    {
      e.join();
    }

    eventList.clear();
    doneList.clear();

    globalTick++;
    if (globalTick > totalTickStep) return 0;
    if (0 == globalTick % 100)
    {
      std::cerr << '.';
    }
  }

  std::cout << "Almost finished ..." << std::endl;

  packetList.clear();

  std::cout << "It works!" << std::endl;

  return 0;
}
