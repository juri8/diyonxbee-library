#ifndef __Dimmer_h_
#define __Dimmer_h_

#include "Actor.h"

class Dimmer : public Actor {
  pin_type pin;
  unsigned int updateDelay = 20; // milliseconds
  unsigned long lastUpdate = 0;
  unsigned char configuredValue;
  unsigned char currentValue;
  unsigned char targetValue;
  public:
    Dimmer(const char* name, pin_type pin);
    virtual void printStatus(Stream& stream);
    virtual void setCommand(const char* const command);
    virtual void execute();
};

#endif
