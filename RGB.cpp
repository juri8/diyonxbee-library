#include "RGB.h"
#include "Arduino.h"

#include "util.h"

RGB::RGB(const char* name, pin_type red, pin_type green, pin_type blue) : Actor(name), redPin(red), greenPin(green), bluePin(blue) {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void RGB::printStatus(Stream& stream) {
    stream.print(name);
    stream.print("=");
    if(targetValue[0] == 0 && configuredValue[0] > 0) 
        stream.println("OFF");
    else {
        stream.print("RGB");
        printByte(stream, configuredValue[0]);
    }
}

void RGB::setCommand(const char* const command) {
    if(strncmp(command, "OFF", 3) == 0) {
        targetValue[0] = 0;
        targetValue[1] = 0;
        targetValue[2] = 0;
    } else if(strncmp(command, "ON", 2) == 0) {
        if(configuredValue[0] == 0 && configuredValue[1] == 0 && configuredValue[2] == 0) {
            configuredValue[0] = 255;
            configuredValue[1] = 255;
            configuredValue[2] = 255;
        }
        targetValue[0] = configuredValue[0];
        targetValue[1] = configuredValue[1];
        targetValue[1] = configuredValue[1];
    } else if(strncmp(command, "RGB", 3) == 0) {
        configuredValue[0] = readColor(command, 3);
        configuredValue[1] = readColor(command, 6);
        configuredValue[2] = readColor(command, 9);
        targetValue[0] = configuredValue[0];
        targetValue[1] = configuredValue[1];
        targetValue[2] = configuredValue[2];
    }
}

unsigned char factor(unsigned char delta0, unsigned char delta1, unsigned char delta2) {
    return abs(delta0) >= max(delta1, delta2) ? 2 : 1;
}

void fade(unsigned char* currentValue, const unsigned char* targetValue) {
        const char delta0 = abs(currentValue[0] - targetValue[0]);
        const char delta1 = abs(currentValue[1] - targetValue[1]);
        const char delta2 = abs(currentValue[2] - targetValue[2]);

        if(currentValue[0] != targetValue[0]) {
            currentValue[0] += getDirection(currentValue[0], targetValue[0]) * factor(delta0, delta1, delta2); 
        }
        if(currentValue[1] != targetValue[1]) {
            currentValue[1] += getDirection(currentValue[1], targetValue[1]) * factor(delta1, delta0, delta2);
        }
        if(currentValue[2] != targetValue[2]) {
            currentValue[2] += getDirection(currentValue[2], targetValue[2]) * factor(delta2, delta0, delta1);
        }
}

void RGB::execute() {
    unsigned long now = millis();
    if(now - lastUpdate > updateDelay) {
        lastUpdate = now;
        fade(currentValue, targetValue);
        analogWrite(redPin, currentValue[0]);
        analogWrite(greenPin, currentValue[1]);
        analogWrite(bluePin, currentValue[2]);
    }
}
