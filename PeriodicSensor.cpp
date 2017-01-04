#include "PeriodicSensor.h"
#include "Arduino.h"

void PeriodicSensor::printStatus(Stream& stream) {
    unsigned long now = millis();
    if(turnOnTime > 0 && !isOn && now - lastUpdate >= queryInterval - turnOnTime) {
        turnOn();
    } else if(now - lastUpdate >= queryInterval) {
        lastUpdate = now;
        stream.print(name);
        stream.print('=');
        printValue(stream);
        if(turnOnTime > 0) {
            turnOff();
        }
    }
}
