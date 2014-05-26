#include "Process.h"

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

  theProc._isRunning = true;
  while (theProc._isRunning) std::this_thread::yield();
}

void Process::WaitFor(Process& theProc, uint64_t latency)
{
  theProc._triggerTick += latency;

  theProc._isRunning = false;
  while (!theProc._isRunning) std::this_thread::yield();
}

void Process::SetFinished(Process& theProc)
{
  theProc._isRunning = false;
  theProc._isFinished = true;
}

bool Process::IsFinished(void)
{
  return _isFinished;
}

bool Process::DesireRun(uint64_t nowTick)
{
  return (nowTick >= _triggerTick);
}

uint64_t Process::GetTriggerTick(void)
{
  return _triggerTick;
}
