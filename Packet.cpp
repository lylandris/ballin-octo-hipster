#include "Packet.h"

using namespace ctc;

Packet::Packet(int len)
{
  _pktLen = len;
  _pkt = new char[_pktLen];
}

Packet::~Packet()
{
}

void
Packet::SetPacketByte(int pos, char byte)
{
  if (0 <= pos && pos < _pktLen)
  {
    _pkt[pos] = byte;
  }
}

int
Packet::GetPacketLen(void)
{
  return _pktLen;
}
