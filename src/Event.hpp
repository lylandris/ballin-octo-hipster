#ifndef __Event_hpp
#define __Event_hpp

#include <vector>
#include <iostream>
#include <algorithm>

#include "Object.hpp"
#include "EventHandler.hpp"

namespace ctc
{
  template <typename... Args> class Event
  {
    public:
      Event& operator+=(EventHandler<Args...> handler)
      {
        handlers_.push_back(handler);
        return *this;
      }
      Event& operator-=(EventHandler<Args...> handler)
      {
        handlers_.erase(std::remove(handlers_.begin(), handlers_.end(), handler), handlers_.end());
        return *this;
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
