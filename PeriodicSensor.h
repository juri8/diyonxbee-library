#ifndef __PeriodicSensor_h_
#define __PeriodicSensor_h_

#include "Sensor.h"

class PeriodicSensor : public Sensor {
  private:
    virtual void printValue(Stream& stream) = 0;
    unsigned long lastUpdate = 0;
  protected:
    const int queryInterval;
    PeriodicSensor(const char* name, const int queryInterval) : Sensor(name), queryInterval(queryInterval) {}
  public:
    virtual void printStatus(Stream& stream);
};

#endif
