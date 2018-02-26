#include "PeriodicSensor.h"
#include "Arduino.h"

void PeriodicSensor::printStatus0(Stream& stream) {
    stream.print(name);
    stream.print('=');
    printValue(stream);
}

void PeriodicSensor::printStatus(Stream& stream) {
    unsigned long now = millis();
    if(turnOnTime > 0 && !isOn && now - lastUpdate >= queryInterval - turnOnTime) {
        turnOn();
    } else if(now - lastUpdate >= queryInterval) {
        lastUpdate = now;
        printStatus0(stream);
        if(turnOnTime > 0) {
            turnOff();
        }
    }
}
