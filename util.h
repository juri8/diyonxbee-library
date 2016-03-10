#ifndef __util_h_
#define __util_h_
#include <Stream.h>

unsigned char readColor(const char* data, const int startIdx);
int getDirection(const unsigned char currentValue, const unsigned char targetValue);
void printByte(Stream& stream, const unsigned char byte); 

#endif
