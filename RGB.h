#ifndef __RGB_h_
#define __RGB_h_

#include "Actor.h"

class RGB : public Actor {
  const unsigned char redPin;
  const unsigned char greenPin;
  const unsigned char bluePin;
  int updateDelay = 20; // milliseconds
  unsigned long lastUpdate = 0;
  unsigned char configuredValue[];
  unsigned char currentValue[];
  unsigned char targetValue[];
  public:
    RGB(const char* name, const unsigned char red, const unsigned char blue, const unsigned char green, Stream& stream) : Actor(name, stream), redPin(red), greenPin(green), bluePin(blue) {};
    virtual void printStatus();
    virtual void setCommand(const char* const command);
    virtual void execute();
};

#endif
