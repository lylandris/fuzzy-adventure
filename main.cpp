#include <iostream>
#include <functional>
#include <forward_list>

#include "Task.h"

int main(int argc, char** argv)
{
  std::forward_list<ctc::Task> fl;
  ctc::Task t1(20);
  ctc::Task t2(230);
  ctc::Task t3(220);
  ctc::Task t4(250);
  ctc::Task t5(120);
  ctc::Task t6(12);

  fl.push_front(t1);
  fl.push_front(t2);
  fl.push_front(t3);
  fl.push_front(t4);
  fl.push_front(t5);
  fl.push_front(t6);

  for (auto& x : fl)
    std::cout << x.GetTick() << std::endl;

  fl.sort();
  std::cout << "After sort..." << std::endl;

  for (auto& x : fl)
    std::cout << x.GetTick() << std::endl;

  std::cout << "It works!" << std::endl;

  return 0;
}
