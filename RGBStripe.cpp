#include "RGBStripe.h"
#include "Arduino.h"

#include "util.h"

RGBStripe::RGBStripe(const char* name, pin_type red, pin_type green, pin_type blue) : Actor(name), redPin(red), greenPin(green), bluePin(blue) {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    configuredValue = { 0, 0, 0};
    currentValue = { 0, 0, 0};
    targetValue = {0, 0, 0};
}

bool isOff(RGB& rgb) {
    return rgb.red == 0 && rgb.green == 0 && rgb.blue == 0;
}

void set(RGB& rgb, color color) {
    rgb.red = rgb.green = rgb.blue = color;
}

void set(RGB& destination, const RGB& source) {
    destination.red = source.red;
    destination.green = source.green;
    destination.blue = source.blue;
}

void RGBStripe::printStatus(Stream& stream) {
    stream.print(name);
    stream.print("=");
    if(isOff(targetValue) && !isOff(configuredValue)) 
        stream.println("OFF");
    else {
        stream.print("RGB");
        printByte(stream, configuredValue.red);
        printByte(stream, configuredValue.green);
        printByte(stream, configuredValue.blue);
        stream.println();
    }
}

void RGBStripe::nextRot() {
    targetValue.red = random(128, 256);
    targetValue.green = random(128, 256);
    targetValue.blue = random(128, 256);

    lastRot = millis();
}

void RGBStripe::setCommand(const char* const command) {
    lastRot = 0;
    if(strncmp(command, "OFF", 3) == 0) {
        set(targetValue, 0);
    } else if(strncmp(command, "ON", 2) == 0) {
        if(isOff(configuredValue)) {
            set(configuredValue, 255);
        }
        set(targetValue, configuredValue);
    } else if(strncmp(command, "RGB", 3) == 0) {
        configuredValue.red = readColor(command, 3);
        configuredValue.green = readColor(command, 6);
        configuredValue.blue = readColor(command, 9);
        set(targetValue, configuredValue);
    } else if(strncmp(command, "ROT", 3) == 0) {
        unsigned int seconds = atoi((const char*)command[3]);
        rotDelay = max(5, seconds) * 1000; 
        nextRot();
    }
}

unsigned char factor(unsigned int delta0, unsigned int delta1, unsigned int delta2) {
    return delta0 > max(delta1, delta2) ? 2 : 1;
}

bool RGBStripe::fade() {
    const int deltaRed = abs(currentValue.red - targetValue.red);
    const int deltaGreen = abs(currentValue.green - targetValue.green);
    const int deltaBlue = abs(currentValue.blue - targetValue.blue);
    bool change = false;
    if(currentValue.red != targetValue.red) {
        currentValue.red += getDirection(currentValue.red, targetValue.red)/* * factor(deltaRed, deltaGreen, deltaBlue)*/; 
        change = true;
    }
    if(currentValue.green != targetValue.green) {
        currentValue.green += getDirection(currentValue.green, targetValue.green)/* * factor(deltaGreen, deltaRed, deltaBlue)*/;
        change = true;
    }
    if(currentValue.blue != targetValue.blue) {
        currentValue.blue += getDirection(currentValue.blue, targetValue.blue)/* * factor(deltaBlue, deltaRed, deltaGreen)*/;
        change = true;
    }
    return change;
}

void RGBStripe::execute() {
    unsigned long now = millis();
    if(lastRot > 0 && now - lastRot > rotDelay) {
        nextRot();
    }
    if(needToFade() && now - lastUpdate > fadeDelay) {
        lastUpdate = now;
        if(fade()) {
            analogWrite(redPin, currentValue.red);
            analogWrite(greenPin, currentValue.green);
            analogWrite(bluePin, currentValue.blue);
        }
    }
}
