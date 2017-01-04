#ifndef __PeriodicSensor_h_
#define __PeriodicSensor_h_

#include "Sensor.h"

class PeriodicSensor : public Sensor {
  private:
    bool isOn = false;
    virtual void printValue(Stream& stream) = 0;
    unsigned long lastUpdate = 0;
    const unsigned int queryInterval;
    const unsigned long turnOnTime; // if greater 0, turnOn will be executed that duration before the actual sensor reading
  protected:
    virtual void turnOn() { isOn = true; };
    virtual void turnOff() { isOn = false; };
    PeriodicSensor(const char* name, const unsigned int queryInterval, const unsigned long aturnOnTime) : Sensor(name), queryInterval(queryInterval), turnOnTime(aturnOnTime) {}
  public:
    virtual void printStatus(Stream& stream);
};

#endif
