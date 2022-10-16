#include <Arduino.h>
#include <TBeam.h>

TBeam tbeam;

void setup() {
  tbeam.begin();
}

void loop() {
  tbeam.update();
  
  if (tbeam.isButtonPressed()){
    Serial.println("PRESSED!");
  }
}