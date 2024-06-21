#ifndef VIBRATION_H
#define VIBRATION_H

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_DRV2605.h"

enum VIBRATION_MODE {
  NONE,
  PULSE,
  HUMM,
  BUZZ
};

class Vibration {
public:
  Vibration(Adafruit_DRV2605*);
  void setVibration(VIBRATION_MODE);
  void start();
  void stop();

private:
  Adafruit_DRV2605* _drv;
  VIBRATION_MODE _currentVibrationMode;
};

#endif  // VIBRATION_H