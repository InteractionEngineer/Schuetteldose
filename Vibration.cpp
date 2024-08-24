#include "Vibration.h"

Vibration::Vibration(Adafruit_DRV2605* drv) {
  _drv = drv;
  _currentVibrationMode = NONE;
}

void Vibration::setVibration(VIBRATION_MODE mode) {

  if (mode == _currentVibrationMode) return;

  switch (mode) {
    case JUMPSTART:
      _drv->setWaveform(0, 1);  // to free the motor if stuck, happens often at low current
      _currentVibrationMode = JUMPSTART;
      break;
    case SPRAY_LIGHT:
      _drv->setWaveform(0, 120);
      _currentVibrationMode = SPRAY_LIGHT;
      break;
    case SPRAY_MEDIUM:
      _drv->setWaveform(0, 119);
      _currentVibrationMode = SPRAY_MEDIUM;
      break;
    case SPRAY_STRONG:
      _drv->setWaveform(0, 65);
      _currentVibrationMode = SPRAY_STRONG;
      break;
    case SPRAY_MAX:
      _drv->setWaveform(0, 64);
      _currentVibrationMode = SPRAY_MAX;
      break;
    case ERROR:
      _drv->setWaveform(0, 118);
      _currentVibrationMode = ERROR;
      break;
    case FILL:
      _drv->setWaveform(0, 70);
      _currentVibrationMode = FILL;
      break;
    default:
      _currentVibrationMode = NONE;
      break;
  }
}

void Vibration::start() {
  _drv->go();
}

void Vibration::stop() {
  _drv->stop();
}