#ifndef __Packet_h
#define __Packet_h

#include "Object.h"

namespace ctc
{
  class Packet : virtual public Object
  {
    public:
      Packet(int len);
      virtual ~Packet() = 0;
      void SetPacketByte(int pos, char byte);
      int GetPacketLen(void);

    private:
      char *_pkt;
      int _pktLen;
  };
}

#endif //__Packet_h
