#include "Task.h"

using namespace ctc;

Task::Task(uint64_t tick, uint64_t interval = 0)
{
  _tick = tick;
  _interval = interval;
}

Task::~Task()
{
}
