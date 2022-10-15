#include <Arduino.h>
#include <Tbeam.h>

Tbeam tbeam;

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