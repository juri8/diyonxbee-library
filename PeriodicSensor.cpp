#include "PeriodicSensor.h"
#include <Arduino.h>

void PeriodicSensor::printStatus() {
    unsigned long now = millis();
    if(lastUpdate + queryInterval >= now) {
        lastUpdate = now;
        serial().print(name);
        serial().print('=');
        printValue();
    }
}
