#include "PacketProcess.h"

#include <iostream>

using namespace ctc;

std::mutex PacketProcess::_m;

PacketProcess::PacketProcess(uint64_t id, size_t len, uint64_t startTick) :
  Packet::Packet(id, len), Process::Process(startTick)
{
  auto x = std::bind(PacketProcess::PerformProcessing, std::ref(*this));
  std::unique_ptr<std::thread> p(new std::thread(x));
  _task = std::move(p);
}

PacketProcess::~PacketProcess(void)
{
  _task->join();
}

void PacketProcess::PrintStatus(PacketProcess& theProc)
{
  std::lock_guard<std::mutex> lock(_m);
  std::cout << "Perform processing for packets <id_" << theProc.GetPacketId() << "@" << theProc.GetTriggerTick() << "> ..." << std::endl;
}

void PacketProcess::PerformProcessing(PacketProcess& theProc)
{
  Process::WaitFor(theProc, 0);
  for (int32_t i = 0; i < 9; i++)
  {
    //for (int i = 0; i < 1000000; i++);
    Process::WaitFor(theProc, 1);
  }

  PacketProcess::PrintStatus(theProc);
  Process::SetFinished(theProc);
}
