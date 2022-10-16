#include <Arduino.h>
#include <TBeam.h>

// default TBEAM_CPU_20 for low energy consumption
// TBeam tbeam();

// use minimum TBEAM_CPU_80 when WiFi is needed
TBeam tbeam(TBEAM_CPU_80);

void setup() {
  tbeam.begin();
}

void loop() {
  tbeam.update();

  tbeam.powerLed(false);
  delay(1000);

  // increase or decrease on demand
  setCpuFrequencyMhz(TBEAM_CPU_240);

  tbeam.powerLed(true);
  delay(1000);
}