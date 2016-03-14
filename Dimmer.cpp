#include "Dimmer.h"
#include "Arduino.h"

#include "util.h"

Dimmer::Dimmer(const char* name, pin_type pin) : Actor(name), pin(pin) {
    pinMode(pin, OUTPUT);
}

void Dimmer::printStatus(Stream& stream) {
    stream.print(name);
    stream.print("=");
    if(targetValue == 0 && configuredValue > 0) 
        stream.println("OFF");
    else {
        stream.print("HUE");
        if(configuredValue < 100 == 0) stream.print('0');
        if(configuredValue < 10 == 0) stream.print('0');
        stream.println(configuredValue);
    }
}

void Dimmer::setCommand(const char* const command) {
    if(strncmp(command, "OFF", 3) == 0) {
        targetValue = 0;
    } else if(strncmp(command, "ON", 2) == 0) {
        if(configuredValue == 0) configuredValue = 255;
        targetValue = configuredValue;
    } else if(strncmp(command, "HUE", 3) == 0) {
        configuredValue = readColor(command, 3);
        targetValue = configuredValue;
    }
}

void Dimmer::execute() {
    unsigned long now = millis();
    if(now - lastUpdate > updateDelay) {
        lastUpdate = now;
        if(currentValue != targetValue) {
            currentValue += getDirection(currentValue, targetValue);
            analogWrite(pin, currentValue);
        }
    }
}
