#include "PacketProcess.h"

#include <iostream>

using namespace ctc;

PacketProcess::PacketProcess(size_t len, uint64_t id) :
  Packet::Packet(len, id)
{
  auto x = std::bind(PacketProcess::PerformProcessing, std::ref(*this));
  std::unique_ptr<std::thread> p(new std::thread(x));
  _task = std::move(p);
}

PacketProcess::~PacketProcess(void)
{
  _task->join();
}

void PacketProcess::PerformProcessing(PacketProcess& theProc)
{
  std::cout << "Starting to perform processing for packets... <id_" <<
    theProc.GetPacketId() << "@" << theProc.GetTick() << ">..." << std::endl;

  for (int32_t i = 0; i < 2000000; i++);
  Process::WaitFor(theProc, 120);
  std::cout << "Starting to perform processing for packets... <id_" <<
    theProc.GetPacketId() << "@" << theProc.GetTick() << ">..." << std::endl;

  for (int32_t i = 0; i < 2000000; i++);
  Process::WaitFor(theProc, 12);
  std::cout << "Starting to perform processing for packets... <id_" <<
    theProc.GetPacketId() << "@" << theProc.GetTick() << ">..." << std::endl;

  for (int32_t i = 0; i < 2000000; i++);
  theProc.SetTaskDone(true);
}
