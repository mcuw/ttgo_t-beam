#include "TBeamGPS.h"

// see https://github.com/LilyGO/TTGO-T-Beam/blob/master/GPS/GPS.ino
TBeamGPS::TBeamGPS(): isActive(false) {
}

TBeamGPS::~TBeamGPS() {
}

void TBeamGPS::begin() {
  isActive = true;

  //TODO pins depend on board
  Serial1.begin(9600, SERIAL_8N1, 12, 34);  // t-beam v0.7 TX=15
}

void TBeamGPS::update() {
  if (!isActive) {
    return;
  }

  // TODO make 2000 value config.
  smartDelay(2000);
}

void TBeamGPS::smartDelay(unsigned long ms)                
{
  unsigned long start = millis();
  do {
    while (Serial1.available()) {
      gps.encode(Serial1.read());
    }
  } while (millis() - start < ms);
}

TinyGPSInteger TBeamGPS::getSatellites() {
  return gps.satellites;
}

TinyGPSTime TBeamGPS::getTime() {
  return gps.time;
}

TinyGPSLocation TBeamGPS::getLocation() {
  return gps.location;
}

TinyGPSAltitude TBeamGPS::getAltitude() {
  return gps.altitude;
}

void TBeamGPS::setActive(bool en) {
  isActive = en;
}