#include "Process.h"

using namespace ctc;

Process::Process(void)
{
  _isTaskDone = false;
}

Process::~Process(void)
{
}

void Process::Notify(Process& theProc, std::atomic<bool>& done)
{
  while (!theProc._isToggle)
  {
    std::this_thread::yield();
  }

  theProc._isToggle = false;

  theProc._currentTick++;
  if (theProc._currentTick < theProc._triggerTick || theProc._isTaskDone)
  {
    done = true;
    return;
  }

  theProc._isFinished = false;
  theProc._isWaiting = false;
  while (!theProc._isFinished)
  {
    std::this_thread::yield();
  }

  done = true;
}

void Process::WaitFor(Process& theProc, uint64_t latency)
{
  theProc._isWaiting = true;
  theProc._triggerTick = theProc._currentTick + latency;
  theProc._isFinished = true;
  while (theProc._isWaiting)
  {
    std::this_thread::yield();
  }
}

uint64_t Process::GetTick(void)
{
  return _currentTick;
}

void Process::SetTaskDone(bool done)
{
  _isTaskDone = done;
}
