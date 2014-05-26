#include "Process.h"

#include <iostream>

using namespace ctc;

Process::Process(uint64_t startTick)
{
  _triggerTick = startTick;
  _isRunning = true;
  _isFinished = false;
}

Process::~Process(void)
{
}

void Process::Notify(Process& theProc, uint64_t nowTick)
{
  if (theProc._isFinished) return;
  if (theProc._isRunning) std::this_thread::yield();
  if (nowTick < theProc._triggerTick)  return;

  std::cout << "[" << std::this_thread::get_id() << "] Trigged @" << nowTick << std::endl;

  theProc._isRunning = true;
  while (theProc._isRunning) std::this_thread::yield();
}

void Process::WaitFor(Process& theProc, uint64_t latency)
{
  theProc._triggerTick += latency;

  std::cout << "[" << std::this_thread::get_id() << "] Paused #" << theProc._triggerTick << std::endl;

  theProc._isRunning = false;
  while (!theProc._isRunning) std::this_thread::yield();
}

void Process::SetFinished(Process& theProc)
{
  std::cout << "[" << std::this_thread::get_id() << "] Finished ..." << std::endl;

  theProc._isRunning = false;
  theProc._isFinished = true;
}

bool Process::IsFinished(void)
{
  return _isFinished;
}
