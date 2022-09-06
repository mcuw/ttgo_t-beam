#ifndef T_BEAM_GPS_H
#define T_BEAM_GPS_H

#include <Arduino.h>
#include <TinyGPS++.h>

class TbeamGPS {
  public:
    TbeamGPS();
    ~TbeamGPS();

    void begin();
    void update();

    void setActive(bool en = true);

    TinyGPSInteger getSatellites();
    TinyGPSTime getTime();
    TinyGPSLocation getLocation();
    TinyGPSAltitude getAltitude();

  private:
    void smartDelay(unsigned long ms);
    bool isActive;
    TinyGPSPlus gps;
    TinyGPSLocation location;
    TinyGPSTime time;
};

#endif
  