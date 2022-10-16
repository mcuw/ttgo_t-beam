#include <Wire.h>
#include <axp20x.h>
#include "TBeamAXP192.h"

TBeamAXP192::TBeamAXP192()
{
  axp = new AXP20X_Class();
}

TBeamAXP192::~TBeamAXP192()
{
  delete axp;
}

bool TBeamAXP192::begin(bool enGPS)
{
  if (!TBeamAXP192::scanI2C(AXP192_ADDRESS))
  {
    Serial.println(F("Could not found AXP192 PMU!"));
    return false;
  }

  if (axp->begin(Wire, AXP192_SLAVE_ADDRESS) == AXP_FAIL)
  {
    Serial.println(F("Failed to begin AXP192 Power!"));
    return false;
  }

  // Set the power of LoRa and GPS module to 3.3V
  axp->setLDO2Voltage(3300);  // LoRa VDD
  axp->setLDO3Voltage(3300);  // GPS  VDD
  axp->setDCDC1Voltage(3300); // 3.3V Pin next to 21 and 22 is controlled by DCDC1

  axp->setPowerOutPut(AXP192_DCDC1, AXP202_ON);
  axp->setPowerOutPut(AXP192_LDO2, AXP202_ON);                      // LoRa radio
  axp->setPowerOutPut(AXP192_LDO3, enGPS ? AXP202_ON : AXP202_OFF); // GPS radio ~40mA
  axp->setChgLEDMode(AXP20X_LED_OFF);                               // blue LED

  // axp->adc1Enable(AXP202_BATT_CUR_ADC1, true); // 0 ohne bat
  // axp->adc1Enable(AXP202_ACIN_CUR_ADC1, true); // 0 ohne bat

  /*
   *   Turn off unused power sources to save power
   * **/
  // PMU.setPowerOutPut(AXP192_DCDC1, AXP202_OFF);
  // PMU.setPowerOutPut(AXP192_DCDC2, AXP202_OFF);
  // PMU.setPowerOutPut(AXP192_LDO2, AXP202_OFF);
  // PMU.setPowerOutPut(AXP192_LDO3, AXP202_OFF);
  // PMU.setPowerOutPut(AXP192_EXTEN, AXP202_OFF);

  // TODO: only on demand? power save?
  axp->adc1Enable(AXP202_VBUS_VOL_ADC1, true);
  axp->adc1Enable(AXP202_VBUS_CUR_ADC1, true);

  // PMU.adc1Enable(AXP202_VBUS_VOL_ADC1 |
  //               AXP202_VBUS_CUR_ADC1 |
  //               AXP202_BATT_CUR_ADC1 |
  //               AXP202_BATT_VOL_ADC1,
  //               AXP202_ON);

  // PMU.enableIRQ(AXP202_VBUS_REMOVED_IRQ |
  //               AXP202_VBUS_CONNECT_IRQ |
  //               AXP202_BATT_REMOVED_IRQ |
  //               AXP202_BATT_CONNECT_IRQ,
  //               AXP202_ON);

  return true;
}

void TBeamAXP192::update()
{
  // Serial.println(axp->getBattChargeCurrent());
  // float v = axp->getVbusVoltage();
  // float c = axp->getVbusCurrent();

  // Serial.print(v); // 5000mV
  // Serial.println("mV");
  // Serial.print(c); // < 30mA
  // Serial.println("mA");
  // Serial.print(v/1000 * c/ 1000); // < 30mA
  // Serial.println("W");

  // Serial.println(axp->getAcinCurrent());
}

bool TBeamAXP192::scanI2C(byte axp192Address)
{
  Wire.beginTransmission(axp192Address);
  byte err = Wire.endTransmission();
  if (err == 0)
  {
    // I2C_ERROR_OK
    return true;
  }

  Serial.print(F("Unknown error at address 0x"));
  Serial.println(axp192Address, HEX);
  return false;
}

void TBeamAXP192::powerGPS(bool en)
{
  axp->setPowerOutPut(AXP192_LDO3, en ? AXP202_ON : AXP202_OFF); // AXP192_LDO3 = GPS power
}

int TBeamAXP192::powerLed(bool en)
{
  return axp->setChgLEDMode(en ? AXP20X_LED_LOW_LEVEL : AXP20X_LED_OFF);
}

int TBeamAXP192::powerLed(TBeamChgLedMode mode)
{
  switch (mode)
  {
  case TBEAM_LED_OFF:
    return axp->setChgLEDMode(AXP20X_LED_OFF);
  case TBEAM_LED_BLINK_1HZ:
    return axp->setChgLEDMode(AXP20X_LED_BLINK_1HZ);
  case TBEAM_LED_BLINK_4HZ:
    return axp->setChgLEDMode(AXP20X_LED_BLINK_4HZ);
  case TBEAM_LED_LOW_LEVEL:
    return axp->setChgLEDMode(AXP20X_LED_LOW_LEVEL);
  default:
    return AXP_FAIL;
  }
}

// axp->setDCDC1Voltage(0); // for the power off ESP
