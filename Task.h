#ifndef __Task_hpp
#define __Task_hpp

#include <cstdint>

#include "Object.h"

namespace ctc
{
  class Task : public Object
  {
    public:
      Task(uint64_t tick, uint64_t interval = 0);
      virtual ~Task();

      bool operator < (const Task& other) const;

      uint64_t GetTick(void);
      uint64_t GetInterval(void);
    private:
      uint64_t _tick;
      uint64_t _interval;
  };
}

#endif //__Task_hpp
