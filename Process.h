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
      Process(void);
      virtual ~Process(void) = 0;

    private:
      std::atomic<bool> _isWaiting;
      std::atomic<bool> _isFinished;
      std::atomic<bool> _isTaskDone;

      uint64_t _triggerTick;
      uint64_t _currentTick;

    protected:
      std::unique_ptr<std::thread> _task;

    public:
      static void Notify(Process& theProc, std::atomic<bool>& done);
      static void WaitFor(Process& theProc, uint64_t latency);

    public:
      uint64_t GetTick(void);
      void SetTaskDone(bool done);
  };
}

#endif //__Process_h
