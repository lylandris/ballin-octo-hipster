#ifndef __Packet_hpp
#define __Packet_hpp

namespace ctc
{
  class Packet : virtual public Object
  {
    public:
      Packet(int len) : _pktLen(len)
      {
        _pkt = new char[_pktLen];
      }
      virtual ~Packet() = 0;
      void SetPacketByte(size_t pos, char byte)
      {
        if (pos < _pktLen)
        {
          _pkt[pos] = byte;
        }
      }
      size_t GetPacketLen(void)
      {
        return _pktLen;
      }

    private:
      char *_pkt;
      size_t _pktLen;
  };
  
  Packet::~Packet()
  {
  }
}

#endif //__Packet_hpp
