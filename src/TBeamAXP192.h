#ifndef T_BEAM_AXP192_H
#define T_BEAM_AXP192_H

#include <Arduino.h>
#include "TBeamDeepsleep.h"
#include "types.h"

#ifndef AXP192_ADDRESS
  #define AXP192_ADDRESS          0x34
#endif
#define AXP_IRQ_PIN             35
#define AXP_GPS_POWER_CTRL_CH   3
#define AXP_LORA_POWER_CTRL_CH  2

class AXP20X_Class;

/**
 * usage:
 * 
 * ```
TBeamAXP192 axp;

void setup() {
  Wire.begin(SDA, SCL);
  axp.begin();
}
```
 */
class TBeamAXP192 {
  public:
    TBeamAXP192();
    ~TBeamAXP192();

    bool begin(bool enGPS = false);
    void update();

    void powerGPS(bool en);
    int powerLed(bool en);
    int powerLed(TBeamChgLedMode mode = TBEAM_LED_LOW_LEVEL);

  private:
    static bool scanI2C(byte axp192Address);
    AXP20X_Class * axp;
    TBeamDeepsleep deepsleep;
};

#endif
