#ifndef __Sensors_h_
#define __Sensors_h_

#include "Sensor.h"
#include "Actor.h"
#include <Stream.h>

class Sensors {
    Stream& stream;
    Sensor** sensors;
    Actor** actors;
    void sendUpdates();
    void processCommand(const char* const item, const char* const command);
    void updateSensors();
    int readBlocking();
  public:
    Sensors(Stream& stream, Sensor** sensors, Actor** actors): stream(stream), sensors(sensors), actors(actors)  {
    }
    void process();
};

#endif
