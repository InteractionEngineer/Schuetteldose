#include "BMS.h"

BMS::BMS(int batteryPin, int usbPin, int thermistorPin) {
  _BATTERY = batteryPin;
  _USB = usbPin;
  _THERMISTOR = thermistorPin;

  _VCC = 3.3;
  _R_FIXED_10 = 10000;

  pinMode(_BATTERY, INPUT);
  pinMode(_USB, INPUT);
  pinMode(_THERMISTOR, INPUT);
}

float BMS::getVoltage() {
  float measuredVBat = analogRead(_BATTERY);
  float batVoltage = measuredVBat * 2 / 1024;
  return batVoltage;
}

bool BMS::isCharging() {
  float measuredVUsb = analogRead(_USB);
  float usbVoltage = measuredVUsb * 2 / 1024;
  return usbVoltage > 4;
}

float BMS::readThermistor() {
  int analogValue = analogRead(_THERMISTOR);
  float Vout = analogValue * (_VCC / 4095.0);
  float R_thermistor = _R_FIXED_10 * (_VCC / Vout - 1.0);
  return R_thermistor;
}