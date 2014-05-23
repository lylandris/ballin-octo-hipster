#ifndef __Process_h
#define __Process_h

#include "Object.h"
#include "Event.h"

namespace ctc
{
  class Process : public EventListener
  {
    public:
      virtual ~Process() = 0;
      virtual void OnEvent(Object *sender) = 0;
  };
}

#endif //__Process_h
