#include "Vibration.h"

Vibration::Vibration(Adafruit_DRV2605* drv) {
  _drv = drv;
  _currentVibrationMode = NONE;
}

void Vibration::setVibration(VIBRATION_MODE mode) {

  if (mode == _currentVibrationMode) return;

  switch (mode) {
    case PULSE:
      _drv->setWaveform(0, 55);  // play effect
      _drv->setWaveform(1, 0);   // end waveform
      _currentVibrationMode = PULSE;
      break;
    case BUZZ:
      _drv->setWaveform(0, 48);  // play effect
      _drv->setWaveform(1, 0);   // end waveform
      _currentVibrationMode = BUZZ;
      break;
    case HUMM:
      _drv->setWaveform(0, 119);  // play effect
      _drv->setWaveform(1, 0);    // end waveform
      _currentVibrationMode = HUMM;
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