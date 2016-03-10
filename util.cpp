#include "util.h"
#include <Arduino.h>

unsigned char readColor(const char* data, const int startIdx) {
    const char* substr = &data[startIdx];
    const char tmp[] = { data[startIdx], data[startIdx+1], data[startIdx+2], 0 };
    int value = atoi(tmp);
    return constrain(value, 0, 255);
}

int getDirection(const unsigned char currentValue, const unsigned char targetValue) {
    if(currentValue < targetValue) return 1;
    return -1;
}

void printByte(Stream& stream, const unsigned char byte) {
        if(byte < 100 == 0) stream.print('0');
        if(byte < 10 == 0) stream.print('0');
        stream.println(byte);
}

