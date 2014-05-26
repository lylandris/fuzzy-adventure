#include "PacketProcess.h"

#include <iostream>

using namespace ctc;

std::mutex PacketProcess::_m;

PacketProcess::PacketProcess(uint64_t id, size_t len) :
  Packet::Packet(id, len), Process::Process(id)
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

  PacketProcess::PrintStatus(theProc);
  Process::WaitFor(theProc, 8);

  PacketProcess::PrintStatus(theProc);
  Process::WaitFor(theProc, 12);

  PacketProcess::PrintStatus(theProc);
  Process::WaitFor(theProc, 22);

  PacketProcess::PrintStatus(theProc);
  Process::WaitFor(theProc, 33);

  PacketProcess::PrintStatus(theProc);
  Process::WaitFor(theProc, 42);

  PacketProcess::PrintStatus(theProc);
  Process::WaitFor(theProc, 62);

  PacketProcess::PrintStatus(theProc);
  Process::SetFinished(theProc);
}
