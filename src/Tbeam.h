#ifndef T_BEAM_H
#define T_BEAM_H

#include <Arduino.h>
#if defined(LILYGO_TBeam_V1_0) || defined(LILYGO_TBeam_V1_1)
#include "TbeamAXP192.h"
#endif
#include "TbeamButton.h"
#include "TbeamDeepsleep.h"
#include "TbeamGPS.h"
#include "types.h"

typedef enum {
  TBEAM_OK = 0,
  TBEAM_AXP_NOT_FOUND = -1,
} TbeamStatus;

typedef enum {
  TBEAM_CPU_240 = 240U,
  TBEAM_CPU_160 = 160U,
  TBEAM_CPU_80 = 80U,
  TBEAM_CPU_40 = 40U,
  TBEAM_CPU_20 = 20U,
  TBEAM_CPU_10 = 10U,
} TbeamCPUfreqMhz;

class Tbeam {
  public:
    Tbeam(TbeamCPUfreqMhz cpuFreqMhz = TBEAM_CPU_20);
    ~Tbeam();

    int begin(bool enGPS = false);
    void update();

    bool isButtonPressed();

    // powerssave
    void hibernate(uint32_t seconds = 1);
    void powerGPS(bool en = true);
    int powerLed(bool en = true);
    int powerLed(TBeamChgLedMode mode = TBEAM_LED_BLINK_1HZ);
    void sleepSeconds(uint32_t seconds = 1);

#if defined(LILYGO_TBeam_V1_0) || defined(LILYGO_TBeam_V1_1)
    TbeamAXP192 getAXP() { return axp; };
#endif
    TbeamButton getButton() { return button; };
    TbeamDeepsleep getDeepsleep() { return deepsleep; };
    TbeamGPS getGPS() { return gps; };

  private:
    uint32_t initialCpuFreqMhz;
    TbeamStatus beginState;
#if defined(LILYGO_TBeam_V1_0) || defined(LILYGO_TBeam_V1_1)
    TbeamAXP192 axp;          // power managment
#endif
    TbeamButton button;       // custom button
    TbeamDeepsleep deepsleep; // powersave
    TbeamGPS gps;             // GPS
};

#endif
