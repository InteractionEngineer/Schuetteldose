#ifndef VIBRATION_H
#define VIBRATION_H

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_DRV2605.h"

enum VIBRATION_MODE {
  NONE,
  JUMPSTART,
  SPRAY_LIGHT,
  SPRAY_MEDIUM,
  SPRAY_STRONG,
  SPRAY_MAX,
  ERROR,
  FILL
};

class Vibration {
public:
  Vibration(Adafruit_DRV2605* drv);
  void setVibration(VIBRATION_MODE mode);
  void start();
  void stop();

private:
  Adafruit_DRV2605* _drv;
  VIBRATION_MODE _currentVibrationMode;
};

#endif  // VIBRATION_H