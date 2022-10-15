#include <Arduino.h>
#include <Tbeam.h>

Tbeam tbeam;

void setup() {
  tbeam.begin(); // optional GPS parameter to enable on start - disabled as default
}

void loop() {
  tbeam.update(); // updates AXP and GPS
  delay(1000);
}