#ifndef __InterruptButton_h_
#define __InterruptButton_h_

#include "Sensor.h"
#include <Arduino.h>

class InterruptButton : public Sensor {
  private:
    pin_type pin;
    bool lastState;
    volatile bool state;
  public:
    InterruptButton(const char* name, pin_type pin);
    virtual void printStatus(Stream& stream);
    void update();
};

#endif
