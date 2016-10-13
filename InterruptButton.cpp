#include "InterruptButton.h"
#include <Arduino.h>

InterruptButton::InterruptButton(const char* name, pin_type pin): Sensor(name), pin(pin), lastState(false), state(false) {
    pinMode(pin, INPUT);
}

void InterruptButton::update() {
    state = digitalRead(pin);
}

void InterruptButton::printStatus(Stream& stream) {
    if(state != lastState) {
        stream.print(name);
        stream.print('=');
        stream.print(state ? "ON" : "OFF");
        lastState = state;
    }
}
