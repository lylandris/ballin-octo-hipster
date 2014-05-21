#ifndef __Packet_hpp
#define __Packet_hpp

#include "Object.hpp"

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

#endif //__Packet_hpp
