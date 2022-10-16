#include "TBeamButton.h"

TBeamButton::TBeamButton(byte buttonPin) 
  : buttonPin(buttonPin) {
  pinMode(buttonPin, INPUT_PULLDOWN);
}

bool TBeamButton::isPressed() {
  return digitalRead(buttonPin) == LOW;
}
