#include "Process.h"

#include <iostream>

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
#if 0
  while (!theProc._isToggle)
  {
    std::this_thread::yield();
  }

  theProc._isToggle = false;
#endif

  theProc._currentTick++;
  if (theProc._currentTick < theProc._triggerTick)
  {
    done = true;
    return;
  }

  if (theProc._isTaskDone)
  {
    theProc._isWaiting = false;
    done = true;
    return;
  }

  std::cout << "[" << std::this_thread::get_id() << "] ";
  std::cout << "Notitied by main, theProc._currentTick=" << theProc._currentTick << std::endl;

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
  std::cout << "[" << std::this_thread::get_id() << "] ";
  theProc._isWaiting = true;
  theProc._triggerTick = theProc._currentTick + latency;
  theProc._isFinished = true;
  std::cout << "Paused, next exec time is " << theProc._triggerTick << std::endl;
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
  std::cout << "[" << std::this_thread::get_id() << "] ";
  _isWaiting = true;
  _isFinished = true;
  std::cout << "The task is finished ..." << std::endl;
  _isTaskDone = done;
  while (_isWaiting)
  {
    std::this_thread::yield();
  }
}
