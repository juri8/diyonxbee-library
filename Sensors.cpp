#include "Sensors.h"

const int MAX_COMMAND = 32;
const int MAX_ITEM = 32;

void Sensors::sendUpdates() {
    const int numberSensors = sizeof(sensors) / sizeof(Sensor*);
    for(int i = 0; i < numberSensors; i++) {
        sensors[i]->printStatus();
    }
}

void Sensors::processCommand(const char* const item, const char* const command) {
    const int count = sizeof(actors) / sizeof(Actor*);
    for(int i = 0; i < count; i++) {
        if(strncmp(item, actors[i]->getName(), MAX_ITEM) == 0) {
            actors[i]->setCommand(command);
        }
    }
}

void Sensors::updateSensors() {
    const int count = sizeof(actors) / sizeof(Actor*);
    for(int i = 0; i < count; i++) {
        actors[i]->execute();
    }
}

int Sensors::readBlocking() {
  while(stream.available() == 0);
  return stream.read();
}

void Sensors::process() {
    if(stream.available() > 0) {
        char item[MAX_ITEM];
        memset(item, '\0', sizeof(item));
        int i = 0;
        for(; i < MAX_ITEM; i++) {
          item[i] = readBlocking();
          if(item[i] == '=') {
            item[i] = '\0';
            break;
          }
        }

        char command[MAX_COMMAND];
        memset(command, '\0', sizeof(command));    
        for(i = 0; i < MAX_COMMAND; i++) {
          command[i] = readBlocking();
          if(command[i] == '\n') {
            command[i] = '\0';
            break;
          }
        }

        processCommand(item, command);
    }
    updateSensors();
    sendUpdates();
}
