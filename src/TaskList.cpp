#include "TaskList.hpp"

#include <iostream>

namespace ctc
{
  void TaskList::callback(Object* sender, int arg1, int arg2)
  {
    std::cout << "Callback from " << sender << " in " << name_ << "! arg1=" << arg1 << " arg2=" << arg2 << std::endl;
  }
}
