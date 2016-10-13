#ifndef __PeriodicSensor_h_
#define __PeriodicSensor_h_

#include "Sensor.h"

class PeriodicSensor : public Sensor {
  private:
    bool isOn = false;
    virtual void printValue(Stream& stream) = 0;
    unsigned long lastUpdate = 0;
    const int queryInterval;
    const int turnOnTime; // if greater 0, turnOn will be executed that duration before the actual sensor reading
  protected:
    virtual void turnOn() { isOn = true; };
    virtual void turnOff() { isOn = false; };
    PeriodicSensor(const char* name, const int queryInterval, const int turnOnTime = 0) : Sensor(name), queryInterval(queryInterval), turnOnTime(turnOnTime) {}
  public:
    virtual void printStatus(Stream& stream);
};

#endif
