#ifndef __Sensors_h_
#define __Sensors_h_

#include "Sensor.h"
#include "Actor.h"
#include <Stream.h>

class Sensors {
    Stream& stream;
    Sensor* sensors[];
    Actor* actors[];
    void sendUpdates();
    void processCommand(const char* const item, const char* const command);
    void updateSensors();
    int readBlocking();
  public:
    Sensors(Stream& stream, const int numSensors, const int numActors): stream(stream) {
        sensors[numSensors];
        actors[numActors];
    }
    void process();
    void setActor(const int actorNum, Actor* actor) {actors[actorNum] = actor; }
    void setSensor(const int sensorNum, Sensor* sensor) { sensors[sensorNum] = sensor; }
};

#endif
