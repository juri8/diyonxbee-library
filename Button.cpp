#include "Button.h"
#include <Arduino.h>

Button::Button(const char* name, pin_type pin): Sensor(name), pin(pin), lastState(false) {
    pinMode(pin, INPUT);
}

void Button::printStatus(Stream& stream) {
    const bool state = digitalRead(pin) == HIGH;
    if(state != lastState) {
        stream.print(name);
        stream.print('=');
        stream.print(state ? "ON" : "OFF");
        lastState = state;
    }
}
