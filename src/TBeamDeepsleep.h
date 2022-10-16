#ifndef T_BEAM_DEEPSLEEP_H
#define T_BEAM_DEEPSLEEP_H

#include <Arduino.h>

class TBeamDeepsleep {
  public:
    TBeamDeepsleep();
    ~TBeamDeepsleep();

    static void sleepInterrupt(uint8_t gpio, uint8_t mode);
    static void sleepInterruptMask(uint64_t mask, uint8_t mode);
    static void sleepMillis(uint64_t ms);
    static void sleepSeconds(uint32_t seconds);
    static void sleepForever();

    static int getRtc();
    static void setRtc(int data);

    static void hibernate(uint32_t seconds);
};

#endif
