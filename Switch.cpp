#include "Switch.h"

#include <Arduino.h>

void Switch::printStatus(Stream& stream) {
    stream.print(name);
    stream.print('=');
    stream.println(state ? "ON" : "OFF");
}

void Switch::setCommand(const char* const command) {
    state = (strcmp(command, "ON") == 0);
}

void Switch::execute() {
    digitalWrite(pin, state ? HIGH : LOW);
}
