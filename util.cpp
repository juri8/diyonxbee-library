#include "util.h"
#include <Arduino.h>

unsigned int readColor(const char* data, const int startIdx) {
    const char tmp[] = { data[startIdx], data[startIdx+1], data[startIdx+2], 0 };
    unsigned int value = atoi(tmp);
    return value;
}

int getDirection(const unsigned int currentValue, const unsigned int targetValue) {
    if(currentValue < targetValue) return 1;
    return -1;
}

void printByte(Stream& stream, const unsigned int byte) {
        if(byte < 100) stream.print('0');
        if(byte < 10) stream.print('0');
        stream.print(byte);
}

int analogReadAverage(const unsigned char pin) {
    int val = analogRead(pin);
    val += analogRead(pin);
    val += analogRead(pin);
    val += analogRead(pin);
    val = val >> 2;
    return val;
}
