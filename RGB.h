#ifndef __RGB_h_
#define __RGB_h_

#include "Actor.h"

class RGB : public Actor {
  pin_type redPin;
  pin_type greenPin;
  pin_type bluePin;
  int updateDelay = 20; // milliseconds
  unsigned long lastUpdate = 0;
  unsigned char configuredValue[];
  unsigned char currentValue[];
  unsigned char targetValue[];
  public:
    RGB(const char* name, pin_type red, pin_type green, pin_type blue);
    virtual void printStatus(Stream& stream);
    virtual void setCommand(const char* const command);
    virtual void execute();
};

#endif
