#ifndef __Actor_h_
#define __Actor_h_

#include "Sensor.h"

class Actor : public Sensor {
  public:
    Actor(const char* name): Sensor(name) {}
    virtual void setCommand(const char* const command) = 0;
    virtual void execute() = 0;
};


#endif
