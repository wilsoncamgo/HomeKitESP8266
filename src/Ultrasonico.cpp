#include "Ultrasonico.h"
#include <Arduino.h>

Ultrasonico::Ultrasonico(byte pinEcho, byte pinTrigger)
{
  // Use 'this->' to make the difference between the
  // 'pin' attribute of the class and the
  // local variable 'pin' created from the parameter.
  this->pinTrigger = pinTrigger;
  this->pinEcho = pinEcho;
}
void Ultrasonico::init()
{
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
}
int Ultrasonico::read()
{

  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
  int time = pulseIn(pinEcho, HIGH, 5000);
  currentDistance = time * 0.1715;
  return currentDistance;
}

//Read not implemented yet