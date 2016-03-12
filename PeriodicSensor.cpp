#include "PeriodicSensor.h"
#include <Arduino.h>

void PeriodicSensor::printStatus(Stream& stream) {
    unsigned long now = millis();
    if(lastUpdate + queryInterval >= now) {
        lastUpdate = now;
        stream.print(name);
        stream.print('=');
        printValue(stream);
    }
}
