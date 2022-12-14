#include <Arduino.h>
#include <TBeam.h>

TBeam tbeam;

void setup() {
  // tbeam.begin(true); // to enable GPS on begin
  tbeam.begin(); // disabled GPS as default to reduce power consumption
}

void loop() {
  tbeam.powerGPS();

  TBeamGPS gps = tbeam.getGPS();
  const satellites = 0;

  do {
    gps.update();
    satellites = gps.getSatellites();
    console.log(satellites);
  } while (satellites < 3)

  tbeam.powerGPS(false);
}