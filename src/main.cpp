#include <iostream>
#include <typeinfo>

#include "TaskList.hpp"
#include "Event.hpp"

using namespace ctc;

typedef Event<int, int> MyCustomEvent;

class MyCustomClass : public Object
{
  public:
    MyCustomEvent onDoSomethingEvent;
    void doSomething()
    {
      std::cout << "MyCustomClass::doSomething()\n";
      onDoSomethingEvent(this, 2, 4);
    }
};

int main(int argc, char **argv)
{
  std::cout << "Hello, world!" << std::endl;
  TaskList a("a"), a2("a2");
  MyCustomClass c;

  c.onDoSomethingEvent += make_handler(a, &TaskList::callback);
  std::cout << "Fire1:\n";
  c.doSomething();

  c.onDoSomethingEvent += make_handler(a2, &TaskList::callback);
  std::cout << "Fire2:\n";
  c.doSomething();

  c.onDoSomethingEvent -= make_handler(a, &TaskList::callback);
  std::cout << "Fire3:\n";
  c.doSomething();

  std::cout << "Fire4:\n";
  c.onDoSomethingEvent(NULL, 99, -42);

  return 0;
}
