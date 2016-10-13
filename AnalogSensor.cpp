#include "AnalogSensor.h"
#include <Arduino.h>

AnalogSensor::AnalogSensor(const char* name, const int pin, const int queryInterval) : PeriodicSensor(name, queryInterval), pin(pin) {
}

void AnalogSensor::printValue(Stream& stream) {
    int value = analogRead(pin);
    value += analogRead(pin);
    value += analogRead(pin);
    value += analogRead(pin);

    stream.println(value>>2);
}
