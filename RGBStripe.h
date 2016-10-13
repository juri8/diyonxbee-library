#ifndef __RGBStripe_h_
#define __RGBStripe_h_

#include "Actor.h"

typedef unsigned char color;

struct RGB {
    color red,green,blue;
};


class RGBStripe : public Actor {
  pin_type redPin;
  pin_type greenPin;
  pin_type bluePin;
  int fadeDelay = 20; // milliseconds
  int rotDelay = 12*60*1000; // 12 minutes
  unsigned long lastRot = 0;
  unsigned long lastUpdate = 0;
  RGB configuredValue;
  RGB currentValue;
  RGB targetValue;
  void nextRot();
  bool fade();
  bool needToFade() { return targetValue.red != currentValue.red || targetValue.green != currentValue.green || targetValue.blue != currentValue.blue; }
  public:
    RGBStripe(const char* name, pin_type red, pin_type green, pin_type blue);
    virtual void printStatus(Stream& stream);
    virtual void setCommand(const char* const command);
    virtual void execute();
};

#endif
