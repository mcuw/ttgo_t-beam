#ifndef T_BEAM_AXP192_H
#define T_BEAM_AXP192_H

#include <Arduino.h>
#include "TbeamDeepsleep.h"

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
TbeamAXP192 axp;

void setup() {
  Wire.begin(SDA, SCL);
  axp.begin();
}
```
 */
class TbeamAXP192 {
  public:
    TbeamAXP192();
    ~TbeamAXP192();

    bool begin(bool enGPS = false);
    void update();

    void powerGPS(bool en);
    void powerLed(bool en);

    void hibernate(uint32_t seconds = 1);

  private:
    static bool scanI2C(byte axp192Address);
    AXP20X_Class * axp;
    TbeamDeepsleep deepsleep;
};

#endif
