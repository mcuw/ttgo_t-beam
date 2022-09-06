#include <Wire.h>
#include <axp20x.h>
#include "TbeamAXP192.h"

TbeamAXP192::TbeamAXP192() {
  axp = new AXP20X_Class();
}

TbeamAXP192::~TbeamAXP192() {
}

bool TbeamAXP192::begin(bool enGPS) {
  if (!TbeamAXP192::scanI2C(AXP192_ADDRESS)) {
    Serial.println(F("Could not found AXP192 PMU!"));
    return false;
  }

  while (axp->begin(Wire, AXP192_SLAVE_ADDRESS) == AXP_FAIL) {
    Serial.println(F("Failed to begin AXP Power!"));
    delay(1000);
  }

  axp->setPowerOutPut(AXP192_LDO2, AXP202_ON); // LORA radio
  axp->setPowerOutPut(AXP192_LDO3, enGPS ? AXP202_ON : AXP202_OFF); // GPS radio ~40mA
  axp->setChgLEDMode(AXP20X_LED_OFF); // blue LED

  axp->setDCDC1Voltage(3300);
  // axp->adc1Enable(AXP202_BATT_CUR_ADC1, true); // 0 ohne bat
  // axp->adc1Enable(AXP202_ACIN_CUR_ADC1, true); // 0 ohne bat

  //TODO: only on demand? power save?
  axp->adc1Enable(AXP202_VBUS_VOL_ADC1, true);
  axp->adc1Enable(AXP202_VBUS_CUR_ADC1, true);

  return true;
}

void TbeamAXP192::update() {
  // Serial.println(axp->getBattChargeCurrent());
  float v = axp->getVbusVoltage();
  float c = axp->getVbusCurrent();

  Serial.print(v); // 5000mV
  Serial.println("mV");
  Serial.print(c); // < 30mA
  Serial.println("mA");
  Serial.print(v/1000 * c/ 1000); // < 30mA
  Serial.println("W");
  // Serial.println(axp->getAcinCurrent());
  
}

bool TbeamAXP192::scanI2C(byte axp192Address)
{
  Wire.beginTransmission(axp192Address);
  byte err = Wire.endTransmission();
  switch (err)
  {
  case I2C_ERROR_OK:
    return true;

  case I2C_ERROR_BUS:
  default:
    Serial.print("Unknow error at address 0x");
    Serial.println(axp192Address, HEX);
    break;
  }

  return false;
}

void TbeamAXP192::powerGPS(bool en) {
  axp->setPowerOutPut(AXP192_LDO3, en ? AXP202_ON : AXP202_OFF); // AXP192_LDO3 = GPS power
}

void TbeamAXP192::powerLed(bool en) {
  axp->setChgLEDMode(en ? AXP20X_LED_LOW_LEVEL : AXP20X_LED_OFF);
}

// axp->setDCDC1Voltage(0); // for the power off ESP
