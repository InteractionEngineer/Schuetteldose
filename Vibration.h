#ifndef VIBRATION_H
#define VIBRATION_H

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_DRV2605.h"

class Vibration
{
public:
    Vibration();
    enum VIBRATION_MODE {
        PULSE,
        HUMM,
        BUZZ
    };
    void setVibration(VIBRATION_MODE mode);
    void start();
    void stop();

private:
    Adafruit_DRV2605 _drv;
    VIBRATION_MODE _currentVibrationMode;
};

#endif // VIBRATION_H