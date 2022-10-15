#include <SPI.h>
#include <Wire.h>
#include "Tbeam.h"

Tbeam::Tbeam(TbeamCPUfreqMhz cpuFreqMhz) : beginState(TBEAM_OK)
{
  initialCpuFreqMhz = getCpuFrequencyMhz();
  setCpuFrequencyMhz(cpuFreqMhz);
}

Tbeam::~Tbeam() {
  setCpuFrequencyMhz(initialCpuFreqMhz);
}

int Tbeam::begin(bool enGPS) {
  // when calling Wire.begin
  // you have to ensure that the first value is an int type
  // because Wire begin() overwrites is error prone
  Wire.begin((int)SDA, SCL);

#if defined(LILYGO_TBeam_V1_0) || defined(LILYGO_TBeam_V1_1)
  if (!axp.begin(enGPS)) {
    return beginState = TBEAM_AXP_NOT_FOUND;
  }
  delay(100);
#endif

  powerGPS(enGPS);

  return TBEAM_OK;
}

void Tbeam::update() {
#if defined(LILYGO_TBeam_V1_0) || defined(LILYGO_TBeam_V1_1)
  if (beginState != TBEAM_AXP_NOT_FOUND) {
    axp.update();
  }
#endif
}

bool Tbeam::isButtonPressed() {
  return button.isPressed();
}

void Tbeam::hibernate(uint32_t seconds) {
  deepsleep.hibernate(seconds);
}

void Tbeam::powerGPS(bool en) {
#if defined(LILYGO_TBeam_V1_0) || defined(LILYGO_TBeam_V1_1)
  axp.powerGPS(en);
#endif

  if (en) {
    gps.begin();
  }
}

int Tbeam::powerLed(bool en) {
#if defined(LILYGO_TBeam_V1_0) || defined(LILYGO_TBeam_V1_1)
  return axp.powerLed(en);
#endif
}

int Tbeam::powerLed(TBeamChgLedMode mode) {
#if defined(LILYGO_TBeam_V1_0) || defined(LILYGO_TBeam_V1_1)
  return axp.powerLed(mode);
#endif
}

void Tbeam::sleepSeconds(uint32_t seconds) {
  deepsleep.sleepSeconds(seconds);
}