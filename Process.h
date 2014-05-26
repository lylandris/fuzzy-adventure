#ifndef __Process_h
#define __Process_h

#include <cstdint>
#include <atomic>
#include <thread>
#include <memory>

#include "Object.h"


namespace ctc
{
  class Process : virtual public Object
  {
    public:
      Process(uint64_t startTick);
      virtual ~Process(void) = 0;

    private:
      std::atomic<bool> _isRunning;
      std::atomic<bool> _isFinished;

      uint64_t _triggerTick;

    protected:
      std::unique_ptr<std::thread> _task;

    public:
      static void Notify(Process& theProc, uint64_t nowTick);
      static void WaitFor(Process& theProc, uint64_t latency);
      static void SetFinished(Process& theProc);

    public:
      bool IsFinished(void);
  };
}

#endif //__Process_h
