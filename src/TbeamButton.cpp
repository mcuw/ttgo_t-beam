#include "TbeamButton.h"

TbeamButton::TbeamButton(byte buttonPin) 
  : buttonPin(buttonPin) {
  pinMode(buttonPin, INPUT_PULLDOWN);
}

bool TbeamButton::isPressed() {
  return digitalRead(buttonPin) == LOW;
}
