#include "Task.h"

using namespace ctc;

Task::Task(uint64_t tick, uint64_t interval)
{
  _tick = tick;
  _interval = interval;
}

Task::~Task()
{
}

bool Task::operator < (const Task& other) const
{
  return _tick < other._tick;
}

uint64_t Task::GetTick(void)
{
  return _tick;
}

uint64_t Task::GetInterval(void)
{
  return _interval;
}
