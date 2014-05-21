#ifndef __PacketProcess_hpp
#define __PacketProcess_hpp

#include <vector>

#include "Object.hpp"
#include "Process.hpp"
#include "Packet.hpp"
#include "PacketInfo.hpp"

namespace ctc
{
  class PacketProcess : public Process, public Packet
  {
    public:
      PacketProcess(int len);
      virtual ~PacketProcess();
    private:
      enum PacketProcessType
      {
        PacketProcessType_MacRx,
        PacketProcessType_NetRx,
        PacketProcessType_Ipe,
        PacketProcessType_BuffStore,
        PacketProcessType_Enqueue,
        PacketProcessType_Dequeue,
        PacketProcessType_BuffRetrv,
        PacketProcessType_Epe,
        PacketProcessType_NetTx,
        PacketProcessType_MacTx,

        PacketProcessType_Max,
      } _curType;


      typedef void (* OnPacketProcess)(PacketProcess& left, PacketInfo& pi);
      OnPacketProcess _OnPacketProcess[PacketProcessType_Max];

      PacketInfo *_arg;

    public:
      void OnEvent(Object *sender);

    private:
      static void TestFunc(PacketProcess& left);
      static void MacRx(PacketProcess& left, PacketInfo& pi);
      static void NetRx(PacketProcess& left, PacketInfo& pi);
      static void Ipe(PacketProcess& left, PacketInfo& pi);
      static void BuffStore(PacketProcess& left, PacketInfo& pi);
      static void Enqueue(PacketProcess& left, PacketInfo& pi);
      static void Dequeue(PacketProcess& left, PacketInfo& pi);
      static void BuffRetrv(PacketProcess& left, PacketInfo& pi);
      static void Epe(PacketProcess& left, PacketInfo& pi);
      static void NetTx(PacketProcess& left, PacketInfo& pi);
      static void MacTx(PacketProcess& left, PacketInfo& pi);

    private:
      static std::vector<PacketProcess*> _gcList;
      typedef void (* OnCollect)(PacketProcess* onePkt);
      static OnCollect _OnCollect;

    public:
      static void RegisterCollectEvent(OnCollect fn);
      static void Collect(void);
  };
}

#endif //__PacketProcess_hpp
