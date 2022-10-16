#include <Arduino.h>
#include <TBeam.h>

TBeam tbeam;

void setup() {
  tbeam.begin();
}

void loop() {
  tbeam.update();

  tbeam.powerLed(true);
  delay(1000);

  tbeam.powerLed(false);
  delay(1000);
}