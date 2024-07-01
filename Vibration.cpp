#include "Vibration.h"

Vibration::Vibration(Adafruit_DRV2605* drv) {
  _drv = drv;
  _currentVibrationMode = NONE;
}

void Vibration::setVibration(VIBRATION_MODE mode) {

  if (mode == _currentVibrationMode) return;

  switch (mode) {
    case SPRAY_LIGHT:
      _drv->setWaveform(0, 120);  // play effect
      _drv->setWaveform(1, 0);    // end waveform
      _currentVibrationMode = SPRAY_LIGHT;
      break;
    case SPRAY_MEDIUM:
      _drv->setWaveform(0, 119);  // play effect
      _drv->setWaveform(1, 0);    // end waveform
      _currentVibrationMode = SPRAY_MEDIUM;
      break;
    case SPRAY_STRONG:
      _drv->setWaveform(0, 65);  // play effect
      _drv->setWaveform(1, 0);   // end waveform
      _currentVibrationMode = SPRAY_STRONG;
      break;
    case SPRAY_MAX:
      _drv->setWaveform(0, 64);  // play effect
      _drv->setWaveform(1, 0);   // end waveform
      _currentVibrationMode = SPRAY_MAX;
      break;
    case ERROR:
      _drv->setWaveform(0, 118);  // play effect
      _drv->setWaveform(1, 0);    // end waveform
      _currentVibrationMode = ERROR;
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