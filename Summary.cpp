#include "Summary.h"
#include <Arduino.h>

Summary::Summary(const char* name, duration queryInterval, duration updateInterval, float multiplier): Sensor(name), state(0), multiplier(multiplier), queryInterval(queryInterval), updateInterval(updateInterval) {
}

void Summary::update() {
    ++state;
}

void Summary::printStatus0(Stream& stream, int value) {
    stream.print(name);
    stream.print('=');
    stream.println(value * multiplier);
}

bool changedEnough(const int value, const int lastValue) {
    const float diff = abs(value - lastValue);
    return diff > 0.1 && diff >= lastValue * 1.1;
}
void Summary::printStatus(Stream& stream) {
    unsigned long now = millis();
    unsigned int duration = now-lastUpdate;
    int value =  state;
    if(duration >= updateInterval || duration > 1000 && changedEnough(value, lastValue)) {
        lastUpdate = now;
        printStatus0(stream, value);
        state = 0;
        lastValue = value;
    }
}

