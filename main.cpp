#include <iostream>
#include <functional>
#include <thread>

#include "SafeQueue.h"

using namespace ctc;

static const size_t FIFO_DEPTH = 4;
static SafeQueue<int> fifo(FIFO_DEPTH);

void PktProc(void)
{
  for (int i = 0; i < 20; i++)
  {
    std::cout << "fifo.Enqueue(" << i << ")" << std::endl;
    fifo.EnQueue(i);
  }
}

void FibProc(void)
{
  for (int i = 0; i < 20; i++)
  {
    for (int i = 0; i < 1000000; i++);
    int x = fifo.DeQueue();
    std::cout << "fifo.Dequeue() is " << x << std::endl;
  }
}

int main(int argc, char** argv)
{
  std::thread pktEngine(PktProc);
  std::thread fibEngine(FibProc);

  pktEngine.join();
  fibEngine.join();

  std::cout << "It works!" << std::endl;

  return 0;
}
