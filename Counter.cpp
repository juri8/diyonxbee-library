#include "Counter.h"
#include <Arduino.h>

Counter::Counter(const char* name, duration queryInterval, duration updateInterval, float multiplier): Sensor(name), state(0), multiplier(multiplier), queryInterval(queryInterval), updateInterval(updateInterval) {
}

void Counter::update() {
    ++state;
}

void Counter::printStatus0(Stream& stream, int value) {
    stream.print(name);
    stream.print('=');
    stream.println(value * multiplier);
}

bool changedEnough(const int value, const int lastValue) {
    const float diff = abs(value - lastValue);
    return diff > 0.1 && diff >= lastValue * 1.1;
}
void Counter::printStatus(Stream& stream) {
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

