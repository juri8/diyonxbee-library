#ifndef __Button_h_
#define __Button_h_

#include "Sensor.h"


class Button : public Sensor {
  private:
    const unsigned char pin;
    bool state, lastReport;
  public:
    Button(const char* name, const unsigned char pin): Sensor(name), pin(pin), state(false), lastReport(false) {};
    virtual void printStatus(Stream& stream);
};

#endif
