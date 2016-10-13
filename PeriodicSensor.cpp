#include "PeriodicSensor.h"
#include <Arduino.h>

void PeriodicSensor::printStatus(Stream& stream) {
    unsigned long now = millis();
    if(turnOnTime > 0 && !isOn && lastUpdate + queryInterval - turnOnTime >= now) {
        turnOn();
    } else if(now - lastUpdate >= queryInterval) {
        lastUpdate = now;
        stream.print(name);
        stream.print('=');
        printValue(stream);
        turnOff();
    }
}
