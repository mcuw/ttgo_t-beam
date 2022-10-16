#include <SPI.h>
#include <Wire.h>
#include "TBeam.h"

TBeam::TBeam(TBeamCPUfreqMhz cpuFreqMhz) : beginState(TBEAM_OK)
{
  initialCpuFreqMhz = getCpuFrequencyMhz();
  setCpuFrequencyMhz(cpuFreqMhz);
}

TBeam::~TBeam() {
  setCpuFrequencyMhz(initialCpuFreqMhz);
}

int TBeam::begin(bool enGPS) {
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

void TBeam::update() {
#if defined(LILYGO_TBeam_V1_0) || defined(LILYGO_TBeam_V1_1)
  if (beginState != TBEAM_AXP_NOT_FOUND) {
    axp.update();
  }
#endif
}

bool TBeam::isButtonPressed() {
  return button.isPressed();
}

void TBeam::hibernate(uint32_t seconds) {
  deepsleep.hibernate(seconds);
}

void TBeam::powerGPS(bool en) {
#if defined(LILYGO_TBeam_V1_0) || defined(LILYGO_TBeam_V1_1)
  axp.powerGPS(en);
#endif

  if (en) {
    gps.begin();
  }
}

int TBeam::powerLed(bool en) {
#if defined(LILYGO_TBeam_V1_0) || defined(LILYGO_TBeam_V1_1)
  return axp.powerLed(en);
#endif
}

int TBeam::powerLed(TBeamChgLedMode mode) {
#if defined(LILYGO_TBeam_V1_0) || defined(LILYGO_TBeam_V1_1)
  return axp.powerLed(mode);
#endif
}

void TBeam::sleepSeconds(uint32_t seconds) {
  deepsleep.sleepSeconds(seconds);
}