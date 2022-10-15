#include <Arduino.h>
#include <Tbeam.h>

Tbeam tbeam;

void setup() {
  tbeam.begin();
}

void loop() {
  tbeam.update();
  
  if (tbeam.isButtonPressed()){
    Serial.println("PRESSED!");
  }
}