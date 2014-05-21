#ifndef __DataStruct_hpp
#define __DataStruct_hpp

#include "Object.hpp"

namespace ctc
{
  class DataStruct : virtual public Object
  {
    public:
      virtual ~DataStruct() = 0;

    private:
  };
}

#endif //__DataStruct_hpp
