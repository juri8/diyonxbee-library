#include "AnalogSensor.h"
#include <Arduino.h>

AnalogSensor::AnalogSensor(const char* name, const int pin, const int queryInterval, Stream& serial) : PeriodicSensor(name, queryInterval, serial), pin(pin) {
}

void AnalogSensor::printValue() {
    int value = analogRead(pin);
    serial().println(value);
}
