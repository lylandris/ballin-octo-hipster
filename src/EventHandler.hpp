#ifndef __EventHandler_hpp
#define __EventHandler_hpp

#include <vector>
#include <typeinfo>
#include <algorithm>

#include "EventListener.hpp"
#include "Object.hpp"

namespace ctc
{
  template <typename... Args> struct EventHandler
  {
    typedef void (EventListener::*BaseCallback)(Object*, Args...);
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

  template <typename T, typename... Args> inline EventHandler<Args...> make_handler(T& object, void (T::*callback)(Object*, Args...))
  {
    return EventHandler<Args...>(object, callback);
  }

}

#endif //__EventHandler_hpp
