#ifndef __Button_h_
#define __Button_h_

#include "Sensor.h"

class Button : public Sensor {
  private:
    pin_type pin;
    bool lastState;
  public:
    Button(const char* name, pin_type pin);
    virtual void printStatus(Stream& stream);
};

#endif
