#ifndef __util_h_
#define __util_h_
#include <Stream.h>

unsigned int readColor(const char* data, const int startIdx);
int getDirection(const unsigned int currentValue, const unsigned int targetValue);
void printByte(Stream& stream, const unsigned int byte); 
int analogReadAverage(const unsigned char analogPin);

#endif
