#include "Dimmer.h"
#include "Arduino.h"

#include "util.h"

void Dimmer::printStatus() {
    serial().print(name);
    serial().print("=");
    if(targetValue == 0 && configuredValue > 0) 
        serial().println("OFF");
    else {
        serial().print("HUE");
        if(configuredValue < 100 == 0) serial().print('0');
        if(configuredValue < 10 == 0) serial().print('0');
        serial().println(configuredValue);
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
    printStatus();
}

void Dimmer::execute() {
    unsigned long now = millis();
    if(now - lastUpdate > updateDelay) {
        lastUpdate = now;
        if(currentValue != targetValue) {
            currentValue += getDirection(currentValue, targetValue);
        }
    }
}
