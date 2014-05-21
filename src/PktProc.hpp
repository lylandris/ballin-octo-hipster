#ifndef __PktProc_hpp
#define __PktProc_hpp

#include <forward_list>

#include "Object.hpp"
#include "Process.hpp"
#include "Packet.hpp"
#include "PacketInfo.hpp"

namespace ctc
{
  class PktProc : public Process, public Packet
  {
    public:
      typedef void (* OnPktProc)(PktProc& left, PacketInfo& pi);
      PktProc(size_t len) : Packet(len)
    {
      _pktProcFuncList[PktProcType_MacRx]     = &PktProc::MacRx;
      _pktProcFuncList[PktProcType_NetRx]     = &PktProc::NetRx;
      _pktProcFuncList[PktProcType_Ipe]       = &PktProc::Ipe;
      _pktProcFuncList[PktProcType_BuffStore] = &PktProc::BuffStore;
      _pktProcFuncList[PktProcType_Enqueue]   = &PktProc::Enqueue;
      _pktProcFuncList[PktProcType_Dequeue]   = &PktProc::Dequeue;
      _pktProcFuncList[PktProcType_BuffRetrv] = &PktProc::BuffRetrv;
      _pktProcFuncList[PktProcType_Epe]       = &PktProc::Epe;
      _pktProcFuncList[PktProcType_NetTx]     = &PktProc::NetTx;
      _pktProcFuncList[PktProcType_MacTx]     = &PktProc::MacTx;

      this->_curType = PktProcType_MacRx;
      this->_arg = new PacketInfo();
    }

      virtual ~PktProc(void)
      {
        if (nullptr != this->_arg)
        {
          delete this->_arg;
          this->_arg = nullptr;
        }
      }
    private:
      enum PktProcType
      {
        PktProcType_MacRx,
        PktProcType_NetRx,
        PktProcType_Ipe,
        PktProcType_BuffStore,
        PktProcType_Enqueue,
        PktProcType_Dequeue,
        PktProcType_BuffRetrv,
        PktProcType_Epe,
        PktProcType_NetTx,
        PktProcType_MacTx,

        PktProcType_Max,
      } _curType;

      static void
        TestFunc(PktProc& left)
        {
          for (size_t i = 0; i < left.GetPacketLen(); i++)
          {
            left.SetPacketByte(i, (i % 256));
          }
        }

      OnPktProc _pktProcFuncList[PktProcType_Max];
      PacketInfo *_arg;

      static void
        MacRx(PktProc& left, PacketInfo& pi)
        {
          left._curType = PktProcType_NetRx;
          TestFunc(left);
        }

      static void
        NetRx(PktProc& left, PacketInfo& pi)
        {
          left._curType = PktProcType_Ipe;
          TestFunc(left);
        }

      static void
        Ipe(PktProc& left, PacketInfo& pi)
        {
          left._curType = PktProcType_BuffStore;
          TestFunc(left);
        }

      static void
        BuffStore(PktProc& left, PacketInfo& pi)
        {
          left._curType = PktProcType_Enqueue;
          TestFunc(left);
        }

      static void
        Enqueue(PktProc& left, PacketInfo& pi)
        {
          left._curType = PktProcType_Dequeue;
          TestFunc(left);
        }

      static void
        Dequeue(PktProc& left, PacketInfo& pi)
        {
          left._curType = PktProcType_BuffRetrv;
          TestFunc(left);
        }

      static void
        BuffRetrv(PktProc& left, PacketInfo& pi)
        {
          left._curType = PktProcType_Epe;
          TestFunc(left);
        }
      static void
        Epe(PktProc& left, PacketInfo& pi)
        {
          left._curType = PktProcType_NetTx;
          TestFunc(left);
        }

      static void
        NetTx(PktProc& left, PacketInfo& pi)
        {
          left._curType = PktProcType_MacTx;
          TestFunc(left);
        }

      static void
        MacTx(PktProc& left, PacketInfo& pi)
        {
          left._curType = PktProcType_Max;
          TestFunc(left);
        }

      static std::vector<PktProc&> _gcList;
      static CollectNoUse(PktProc& left)
      {
        _gcList.push_back(left);
      }

    public:
      typedef void (*CollectCallback)(PktProc& onePkt);
      static CollectCallback _GcCallback;
      static void RegisterCollectFunc(CollectCallback func)
      {
        _GcCallback = func;
      }
      static void Collect(void)
      {
        if (nullptr != _GcCallback)
        {
          for (PktProc& pkt : _gcList)
          {
            _GcCallback(pkt);
          }
        }

        _gcList.clear();
      }

      void callback(Object *sender)
      {
        if (this->_curType >= PktProcType_Max)
        {
          CollectNoUse(*this);
        }
        else if (nullptr != _pktProcFuncList[this->_curType])
        {
          (*_pktProcFuncList[this->_curType])((*this), (*(this->_arg)));
        }
      }
  };
}

#endif //__PktProc_hpp
