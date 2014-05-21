#ifndef __Process_hpp
#define __Process_hpp

#include "Object.hpp"
#include "Event.hpp"
#include "PacketInfo.hpp"

namespace ctc
{
  class Process : public EventListener
  {
    public:
      virtual ~Process() = 0;
      virtual void callback(Object *sender) = 0;
  };
  
  Process::~Process()
  {
  }
}

#endif //__Process_hpp
