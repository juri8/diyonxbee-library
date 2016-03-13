#ifndef __Switch_h_
#define __Switch_h_

#include "Actor.h"

class Switch : public Actor {
  private:
    const unsigned char pin;
    bool state;
  public:
    Switch(const char* name, const unsigned char pin): Actor(name), pin(pin), state(false) {}
    virtual void setCommand(const char* const command);
    virtual void execute();
    virtual void printStatus(Stream& stream);
};

#endif
