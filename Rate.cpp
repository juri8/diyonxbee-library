#include "Rate.h"
#include <Arduino.h>

Rate::Rate(const char* name, duration queryInterval, duration updateInterval, float multiplier): Sensor(name), state(0), multiplier(multiplier), queryInterval(queryInterval), updateInterval(updateInterval) {
}

void Rate::update() {
    ++state;
}

void Rate::printStatus0(Stream& stream, float value) {
    stream.print(name);
    stream.print('=');
    stream.println(value * multiplier);
}

bool changedEnough(const float value, const float lastValue) {
    const float diff = abs(value - lastValue);
    return diff > 0.1 && diff >= lastValue * 1.1;
}
void Rate::printStatus(Stream& stream) {
    unsigned long now = millis();
    unsigned int duration = now-lastUpdate;
    float value =  state / (duration / 1000.0); // per seconds
    if(duration >= updateInterval || duration > 1000 && changedEnough(value, lastValue)) {
        lastUpdate = now;
        printStatus0(stream, value);
        state = 0;
        lastValue = value;
    }
}

