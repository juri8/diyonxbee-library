#ifndef __Dimmer_h_
#define __Dimmer_h_

#include "Actor.h"

class Dimmer : public Actor {
  const unsigned char pin;
  unsigned int updateDelay = 20; // milliseconds
  unsigned long lastUpdate = 0;
  unsigned char configuredValue;
  unsigned char currentValue;
  unsigned char targetValue;
  public:
    Dimmer(const char* name, const unsigned char pin, Stream& stream) : Actor(name, stream), pin(pin) {};
    virtual void printStatus();
    virtual void setCommand(const char* const command);
    virtual void execute();
};

#endif
