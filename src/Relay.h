#ifndef RELAY_H
#define RELAY_H
#include <Arduino.h>
#include "sensor.h"

class Relay : public Sensor
{

private:
  byte pinEnable;
  bool currentState;

public:
  Relay(byte pinEnable);
  void init();
  int read();
  void my_homekit_loop();
};
#endif