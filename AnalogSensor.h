#ifndef __AnalogSensor_h_
#define __AnalogSensor_h_

#include "PeriodicSensor.h"

class AnalogSensor : public PeriodicSensor {
  private:
    const int pin;
    virtual void printValue();
  public:
    AnalogSensor(const char* name, const int pin, const int queryInterval, Stream& serial);
};

#endif
