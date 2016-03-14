#ifndef __Sensor_h_
#define __Sensor_h_

#include <Stream.h>

typedef const unsigned char pin_type;

class Sensor {
  private:
  protected:
    const char* name;
  public:
    Sensor(const char* name): name(name) {};
    virtual void printStatus(Stream& stream) = 0;
    const char* getName() { return name; }
};


#endif
