#ifndef __PacketInfo_h
#define __PacketInfo_h

#include "DataStruct.h"

namespace ctc
{
  class PacketInfo : virtual public DataStruct
  {
    public:
      PacketInfo();
      virtual ~PacketInfo();

    private:
  };
}

#endif //__PacketInfo_h
