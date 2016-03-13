#include "Button.h"
#include <Arduino.h>

void Button::printStatus(Stream& stream) {
    if(state != lastReport) {
        stream.print(name);
        stream.print('=');
        stream.print(state ? "ON" : "OFF");
        lastReport = state;
    }
}
