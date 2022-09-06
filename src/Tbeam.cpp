#include <SPI.h>
#include <Wire.h>
#include "Tbeam.h"

Tbeam::Tbeam() : beginState(TBEAM_OK) {
}

Tbeam::~Tbeam() {
}

int Tbeam::begin(uint32_t cpuFreqMhz, bool enGPS) {
  setCpuFrequencyMhz(cpuFreqMhz);

  Wire.begin(SDA, SCL);
  if (!axp.begin(enGPS)) {
    return beginState = TBEAM_AXP_NOT_FOUND;
  }

  powerGPS(enGPS);

  return 0;
}

void Tbeam::update() {
  if (beginState != TBEAM_AXP_NOT_FOUND) {
    axp.update();
  }
  gps.update();
}

bool Tbeam::isButtonPressed() {
  return button.isPressed();
}

void Tbeam::hibernate() {
  axp.hibernate();
}

void Tbeam::powerGPS(bool en) {
  axp.powerGPS(en);
  if (en) {
    gps.begin();
  }
}

void Tbeam::powerLed(bool en) {
  axp.powerLed(en);
}

void Tbeam::sleepSeconds(uint32_t seconds) {
  deepsleep.sleepSeconds(seconds);
}