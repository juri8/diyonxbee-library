#ifndef __Counter_h_
#define __Counter_h_

#include "Sensor.h"
#include <Arduino.h>

typedef const unsigned int duration; 

class Counter : public Sensor {
  private:
    volatile int state;
    const float multiplier;
    duration queryInterval;
    duration updateInterval;
    unsigned long lastUpdate = 0;
    int lastValue = 0;
    virtual void printStatus0(Stream&, int);
  public:
    Counter(const char* name, duration queryInterval, duration updateInterval, float multiplier = 1);
    void update();
    virtual void printStatus(Stream& stream);
};

#endif
