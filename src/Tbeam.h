#ifndef T_BEAM_H
#define T_BEAM_H

#include <Arduino.h>
#include "TBeamAXP192.h"
#include "TbeamButton.h"
#include "TbeamDeepsleep.h"
#include "TbeamGPS.h"

typedef enum {
  TBEAM_OK = 0,
  TBEAM_AXP_NOT_FOUND = -1,
} TbeamStatus;

class Tbeam {
  public:
    Tbeam();
    ~Tbeam();

    int begin(uint32_t cpu_freq_mhz = 20, bool enGPS = false);
    void update();

    bool isButtonPressed();

    // powerssave
    void hibernate();
    void powerGPS(bool en = true);
    void powerLed(bool en = true);
    void sleepSeconds(uint32_t seconds = 1);

    TbeamAXP192 getAXP() { return axp; };
    TbeamButton getButton() { return button; };
    TbeamDeepsleep getDeepsleep() { return deepsleep; };
    TbeamGPS getGPS() { return gps; };

  private:
    TbeamStatus beginState;
    TbeamAXP192 axp;          // power managment
    TbeamButton button;       // custom button
    TbeamDeepsleep deepsleep; // powersave
    TbeamGPS gps;             // GPS
    //LoRa
};

#endif
