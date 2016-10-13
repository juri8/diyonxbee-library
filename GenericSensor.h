#ifndef __GenericSensor_h_
#define __GenericSensor_h_

#include "PeriodicSensor.h"

typedef void (*switchfunc)(const bool on);
typedef void (*readfunc)(Stream& stream);

class GenericSensor : public PeriodicSensor {
  private:
    readfunc function;
    switchfunc switch_function;
    virtual void printValue(Stream& stream) { function(stream); }
    virtual void turnOn() { switch_function(true); PeriodicSensor::turnOn(); }
    virtual void turnOff() { switch_function(false); PeriodicSensor::turnOff(); }
  public:
    GenericSensor(const char* name, const int queryInterval, readfunc function, const int turnOnTime = 0, switchfunc switch_function = NULL) : PeriodicSensor(name, queryInterval, turnOnTime), function(function), switch_function(switch_function){}
};
#endif
