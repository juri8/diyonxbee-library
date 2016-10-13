#include "Sensors.h"

const int MAX_COMMAND = 32;
const int MAX_ITEM = 32;

void Sensors::sendUpdates() {
    const unsigned char numSensors = sensors != NULL ? sizeof(sensors) / sizeof(Sensor*) : 0;
    for(unsigned char i = 0; i < numSensors; i++) {
        sensors[i]->printStatus(stream);
    }
}

void Sensors::processCommand(const char* const item, const char* const command) {
    const unsigned char numActors = actors != NULL ? sizeof(actors) / sizeof(Actor*) : 0;
    for(unsigned char i = 0; i < numActors; i++) {
        if(strncmp(item, actors[i]->getName(), MAX_ITEM) == 0) {
//            stream.print("updating actor ");
//            stream.println(actors[i]->getName());
            actors[i]->setCommand(command);
            actors[i]->printStatus(stream);
            break;
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
        //stream.println(item);

        char command[MAX_COMMAND];
        memset(command, '\0', sizeof(command));    
        for(i = 0; i < MAX_COMMAND; i++) {
          command[i] = readBlocking();
          if(command[i] == '\n') {
            command[i] = '\0';
            break;
          }
        }
        //stream.println(command);

        processCommand(item, command);
    }
    updateSensors();
    sendUpdates();
}
