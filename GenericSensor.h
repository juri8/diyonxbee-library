#ifndef __GenericSensor_h_
#define __GenericSensor_h_

#include "PeriodicSensor.h"

class GenericSensor : public PeriodicSensor {
  private:
    void (*function)(Stream& stream);
    virtual void printValue(Stream& stream) { function(stream); }
  public:
    GenericSensor(const char* name, const int queryInterval, void (*function)(Stream& stream)) : PeriodicSensor(name, queryInterval), function(function) {}
};
#endif
