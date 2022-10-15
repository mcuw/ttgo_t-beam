#include <Arduino.h>
#include <Tbeam.h>

Tbeam tbeam;

void setup() {
  tbeam.begin();

  tbeam.powerLed(true);
  delay(1000);
  tbeam.powerLed(false);

  tbeam.sleepSeconds(1);
}

void loop() {
  // will never reach here
}