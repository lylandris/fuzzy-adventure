#ifndef __Task_hpp
#define __Task_hpp

#include <cstdint>

#include "Object.h"

namespace ctc
{
  class Task : public Object
  {
    public:
      Task(uint64_t tick, uint64_t interval);
      virtual ~Task() = 0;
    private:
      uint64_t _tick;
      uint64_t _interval;
  };
}

#endif //__Task_hpp
