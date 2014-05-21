#include <iostream>
#include <typeinfo>

#include "Event.hpp"
#include "PktProc.hpp"
#include "PacketInfo.hpp"

using namespace ctc;

typedef Event<> _ClockCore;

class ClockCore : public Object
{
  public:
    _ClockCore onDoSomethingEvent;
    void doSomething()
    {
      onDoSomethingEvent(this);
    }
};

int main(int argc, char **argv)
{
  ClockCore clkCore;

  const double clkCoreInterval = ((double) 1.0) / 600000000;
  const double clkNetInterval = ((double) 64) * 8 / 1000000000;

  double clockCoreTime = 0.0;
  double clockNetTime = 0.0;

  while (true)
  {
    if (clockCoreTime > 1.0 && clockNetTime > 1.0)
    {
      break;
    }
    else if (clockCoreTime > clockNetTime)
    {
      clockNetTime += clkNetInterval;
      PktProc *onePkt = new PktProc(64);
      clkCore.onDoSomethingEvent += EventHandlerFactory((*onePkt), &PktProc::callback);
    }
    else
    {
      clockCoreTime += clkCoreInterval;
      clkCore.doSomething();
    }
  }

  return 0;
}
