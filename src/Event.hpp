#ifndef __Event_hpp
#define __Event_hpp

#include <vector>
#include <typeinfo>
#include <algorithm>

#include "Object.hpp"

namespace ctc
{
  class EventListener
  {
    public:
      virtual ~EventListener() = 0;
  };

  template <typename... Args> struct EventHandler
  {
    typedef void (EventListener::* BaseCallback)(Object*, Args...);
    EventListener* listener_;
    BaseCallback   callback_;
    template <typename T> EventHandler(T& listener, void (T::* callback)(Object*, Args...))
      : listener_(&listener), callback_(static_cast<BaseCallback>(callback))
    {
    }
    bool operator==(const EventHandler& other) const
    {
      return (listener_ == other.listener_) && (callback_ == other.callback_);
    }
  };

  template <typename T, typename... Args>
    inline EventHandler<Args...>
    EventHandlerFactory(T& object, void (T::* callback)(Object*, Args...))
    {
      return EventHandler<Args...>(object, callback);
    }

  template <typename... Args> class Event
  {
    public:
      virtual ~Event(void) {};
      Event& operator+=(EventHandler<Args...> handler)
      {
        handlers_.push_back(handler);
        return (*this);
      }
      Event& operator-=(EventHandler<Args...> handler)
      {
        handlers_.erase(std::remove(handlers_.begin(), handlers_.end(), handler), handlers_.end());
        return (*this);
      }
      void operator()(Object* sender, Args... args)
      {
        for ( EventHandler<Args...>& handler : handlers_ )
          (handler.listener_->*handler.callback_)(sender, args...);
      }
    protected:
      std::vector<EventHandler<Args...>> handlers_;
  };
}

#endif //__Event_hpp
