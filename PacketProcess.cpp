#include "PacketProcess.h"

#include <iostream>

using namespace ctc;

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

void PacketProcess::PerformProcessing(PacketProcess& theProc)
{
  std::cout << "Starting to perform processing for packets... <id_" <<
    theProc.GetPacketId() << "> ..." << std::endl;

  //for (int32_t i = 0; i < 2000000; i++);
  Process::WaitFor(theProc, 8);

  std::cout << "Starting to perform processing for packets... <id_" <<
    theProc.GetPacketId() << "> ..." << std::endl;

  //for (int32_t i = 0; i < 2000000; i++);
  Process::WaitFor(theProc, 12);

  std::cout << "Starting to perform processing for packets... <id_" <<
    theProc.GetPacketId() << "> ..." << std::endl;

  //for (int32_t i = 0; i < 2000000; i++);
  Process::WaitFor(theProc, 22);

  std::cout << "Starting to perform processing for packets... <id_" <<
    theProc.GetPacketId() << "> ..." << std::endl;

  //for (int32_t i = 0; i < 2000000; i++);
  Process::WaitFor(theProc, 33);

  std::cout << "Starting to perform processing for packets... <id_" <<
    theProc.GetPacketId() << "> ..." << std::endl;

  //for (int32_t i = 0; i < 2000000; i++);
  Process::WaitFor(theProc, 42);

  std::cout << "Starting to perform processing for packets... <id_" <<
    theProc.GetPacketId() << "> ..." << std::endl;

  //for (int32_t i = 0; i < 2000000; i++);
  Process::WaitFor(theProc, 62);

  std::cout << "Starting to perform processing for packets... <id_" <<
    theProc.GetPacketId() << "> ..." << std::endl;

  //for (int32_t i = 0; i < 2000000; i++);
  Process::SetFinished(theProc);
}
