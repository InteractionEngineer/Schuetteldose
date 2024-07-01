#ifndef BMS_H
#define BMS_H

#include <Arduino.h>

class BMS
{
public:
    BMS(int batteryPin, int usbPin, int thermistorPin);
    float getVoltage();
    bool isCharging();
    float readThermistor();

private:
    int _BATTERY;
    int _USB;
    int _THERMISTOR;
    float _VCC;
    int _R_FIXED_10;
};

#endif // BMS_H