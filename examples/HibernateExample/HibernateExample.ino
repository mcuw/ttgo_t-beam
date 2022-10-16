#include <Arduino.h>
#include <TBeam.h>

TBeam tbeam;

void setup() {
  tbeam.begin();

  tbeam.powerLed(true);
  delay(1000);
  tbeam.powerLed(false);

  tbeam.hibernate(1);
}

void loop() {
  // will never reach here
}