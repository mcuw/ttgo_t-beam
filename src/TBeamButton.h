#ifndef T_BEAM_BUTTON_H
#define T_BEAM_BUTTON_H

#include <Arduino.h>

#define PIN_SW1 38

/**
 * usage:
 * 
 * ```
TBeamButton btn;

void loop() {
  if (btn.isPressed()){
    Serial.println("PRESSED!");
  }
  else {
    Serial.println("NOT PRESSED!");
  }
}
```
 */
class TBeamButton {
  public:
    TBeamButton(byte buttonPin = PIN_SW1);
    ~TBeamButton() {};

    bool isPressed();

  private:
    byte buttonPin;
};

#endif
