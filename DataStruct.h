#ifndef __DataStruct_h
#define __DataStruct_h

#include "Object.h"

namespace ctc
{
  class DataStruct : virtual public Object
  {
    public:
      virtual ~DataStruct() = 0;

    private:
  };
}

#endif //__DataStruct_h
