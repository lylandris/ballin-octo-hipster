#include <iostream>
#include <typeinfo>

#include "Event.hpp"
#include "PacketProcess.hpp"

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

ClockCore clkCore;

void
DeleteEventHandler(PacketProcess* onePkt)
{
  clkCore.onDoSomethingEvent -= EventHandlerFactory((*onePkt), &PacketProcess::OnEvent);
  delete onePkt;
}

int main(int argc, char **argv)
{
  const double clkCoreInterval = ((double) 1.0) / 600000000;
  const double clkNetInterval = ((double) 64) * 8 / 1000000000;

  double clockCoreTime = 0.0;
  double clockNetTime = 0.0;
  
  PacketProcess::RegisterCollectEvent(&DeleteEventHandler);

  while (true)
  {
    if (clockCoreTime > 1.0 && clockNetTime > 1.0)
    {
      break;
    }
    else if (clockCoreTime > clockNetTime)
    {
      clockNetTime += clkNetInterval;
      PacketProcess *onePkt = new PacketProcess(64);
      clkCore.onDoSomethingEvent += EventHandlerFactory((*onePkt), &PacketProcess::OnEvent);
    }
    else
    {
      clockCoreTime += clkCoreInterval;
      clkCore.doSomething();
      PacketProcess::Collect();
    }
  }

  return 0;
}
