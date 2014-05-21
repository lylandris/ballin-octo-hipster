#ifndef __Process_hpp
#define __Process_hpp

#include "Object.hpp"
#include "Event.hpp"

namespace ctc
{
  class Process : public EventListener
  {
    public:
      virtual ~Process() = 0;
      virtual void OnEvent(Object *sender) = 0;
  };
}

#endif //__Process_hpp
