#include "AnalogSensor.h"
#include <Arduino.h>
#include "util.h"

AnalogSensor::AnalogSensor(const char* name, const int pin, const int queryInterval) : PeriodicSensor(name, queryInterval, 0), pin(pin) {
}

void AnalogSensor::printValue(Stream& stream) {
    int value = analogReadAverage(pin);
    stream.println(value);
}
