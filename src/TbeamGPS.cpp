#include "TbeamGPS.h"

// see https://github.com/LilyGO/TTGO-T-Beam/blob/master/GPS/GPS.ino
TbeamGPS::TbeamGPS(): isActive(false) {
}

TbeamGPS::~TbeamGPS() {
}

void TbeamGPS::begin() {
  isActive = true;

  //TODO pins depend on board
  Serial1.begin(9600, SERIAL_8N1, 12, 34);  // t-beam v0.7 TX=15
}

void TbeamGPS::update() {
  if (!isActive) {
    return;
  }

  // TODO make 2000 value config.
  smartDelay(2000);
}

void TbeamGPS::smartDelay(unsigned long ms)                
{
  unsigned long start = millis();
  do {
    while (Serial1.available()) {
      gps.encode(Serial1.read());
    }
  } while (millis() - start < ms);
}

TinyGPSInteger TbeamGPS::getSatellites() {
  return gps.satellites;
}

TinyGPSTime TbeamGPS::getTime() {
  return gps.time;
}

TinyGPSLocation TbeamGPS::getLocation() {
  return gps.location;
}

TinyGPSAltitude TbeamGPS::getAltitude() {
  return gps.altitude;
}

void TbeamGPS::setActive(bool en) {
  isActive = en;
}