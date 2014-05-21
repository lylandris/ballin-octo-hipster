#ifndef __PacketInfo_hpp
#define __PacketInfo_hpp

#include "DataStruct.hpp"

namespace ctc
{
  class PacketInfo : virtual public DataStruct
  {
    public:
      PacketInfo()
      {
      }

      virtual ~PacketInfo()
      {
      }

    private:
  };
}

#endif //__PacketInfo_hpp
