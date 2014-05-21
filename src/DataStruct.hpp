#ifndef __DataStruct_hpp
#define __DataStruct_hpp

namespace ctc
{
  class DataStruct : virtual public Object
  {
    public:
      virtual ~DataStruct() = 0;

    private:
  };
  
  DataStruct::~DataStruct()
  {
  }
}

#endif //__DataStruct_hpp
