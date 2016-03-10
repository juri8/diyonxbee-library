#ifndef __Sensor_h_
#define __Sensor_h_

#include <Stream.h>

class Sensor {
  private:
    Stream& _serial;
  protected:
    const char* name;
    Stream& serial() { return _serial; }
  public:
    Sensor(const char* name, Stream& aSerial): name(name), _serial(aSerial) {};
    virtual void printStatus() = 0;
    const char* getName() { return name; }
};


#endif
