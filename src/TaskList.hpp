#ifndef __TaskList_hpp
#define __TaskList_hpp

#include "Object.hpp"
#include "EventListener.hpp"

namespace ctc
{
  class TaskList : public EventListener
  {
    public:
      TaskList(const char* name) : name_(name) {}
      void callback(Object* sender, int arg1, int arg2);
    protected:
      const char* name_;
  };
}

#endif //__TaskList_hpp
