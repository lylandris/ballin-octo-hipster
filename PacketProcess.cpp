#include "PacketProcess.h"

#include <vector>

using namespace ctc;
using namespace std;

std::vector<PacketProcess*> PacketProcess::_gcList;
PacketProcess::OnCollect PacketProcess::_OnCollect = nullptr;

PacketProcess::PacketProcess(int len) : Packet(len)
{
  _OnPacketProcess[PacketProcessType_MacRx]     = &PacketProcess::MacRx;
  _OnPacketProcess[PacketProcessType_NetRx]     = &PacketProcess::NetRx;
  _OnPacketProcess[PacketProcessType_Ipe]       = &PacketProcess::Ipe;
  _OnPacketProcess[PacketProcessType_BuffStore] = &PacketProcess::BuffStore;
  _OnPacketProcess[PacketProcessType_Enqueue]   = &PacketProcess::Enqueue;
  _OnPacketProcess[PacketProcessType_Dequeue]   = &PacketProcess::Dequeue;
  _OnPacketProcess[PacketProcessType_BuffRetrv] = &PacketProcess::BuffRetrv;
  _OnPacketProcess[PacketProcessType_Epe]       = &PacketProcess::Epe;
  _OnPacketProcess[PacketProcessType_NetTx]     = &PacketProcess::NetTx;
  _OnPacketProcess[PacketProcessType_MacTx]     = &PacketProcess::MacTx;

  this->_curType = PacketProcessType_MacRx;
  this->_arg = new PacketInfo();
}

PacketProcess::~PacketProcess()
{
  if (nullptr != this->_arg)
  {
    delete this->_arg;
    this->_arg = nullptr;
  }
}

void
PacketProcess::TestFunc(PacketProcess& left)
{
  for (int i = 0; i < left.GetPacketLen(); i++)
  {
    left.SetPacketByte(i, (i % 256));
  }
}

void
PacketProcess::MacRx(PacketProcess& left, PacketInfo& pi)
{
  left._curType = PacketProcessType_NetRx;
  TestFunc(left);
}

void
PacketProcess::NetRx(PacketProcess& left, PacketInfo& pi)
{
  left._curType = PacketProcessType_Ipe;
  TestFunc(left);
}

void
PacketProcess::Ipe(PacketProcess& left, PacketInfo& pi)
{
  left._curType = PacketProcessType_BuffStore;
  TestFunc(left);
}

void
PacketProcess::BuffStore(PacketProcess& left, PacketInfo& pi)
{
  left._curType = PacketProcessType_Enqueue;
  TestFunc(left);
}

void
PacketProcess::Enqueue(PacketProcess& left, PacketInfo& pi)
{
  left._curType = PacketProcessType_Dequeue;
  TestFunc(left);
}

void
PacketProcess::Dequeue(PacketProcess& left, PacketInfo& pi)
{
  left._curType = PacketProcessType_BuffRetrv;
  TestFunc(left);
}

void
PacketProcess::BuffRetrv(PacketProcess& left, PacketInfo& pi)
{
  left._curType = PacketProcessType_Epe;
  TestFunc(left);
}

void
PacketProcess::Epe(PacketProcess& left, PacketInfo& pi)
{
  left._curType = PacketProcessType_NetTx;
  TestFunc(left);
}

void
PacketProcess::NetTx(PacketProcess& left, PacketInfo& pi)
{
  left._curType = PacketProcessType_MacTx;
  TestFunc(left);
}

void
PacketProcess::MacTx(PacketProcess& left, PacketInfo& pi)
{
  left._curType = PacketProcessType_Max;
  TestFunc(left);
}

void
PacketProcess::RegisterCollectEvent(OnCollect fn)
{
  _OnCollect = fn;
}

void
PacketProcess::Collect(void)
{
  if (nullptr != _OnCollect)
  {
    for (PacketProcess* pkt : _gcList)
    {
      (*_OnCollect)(pkt);
    }
  }

  _gcList.clear();
}

void
PacketProcess::OnEvent(Object *sender)
{
  if (this->_curType >= PacketProcessType_Max)
  {
    _gcList.push_back(this);
  }
  else if (nullptr != _OnPacketProcess[this->_curType])
  {
    (*_OnPacketProcess[this->_curType])((*this), (*(this->_arg)));
  }
}
