#include "Vibration.h"

Vibration::Vibration()
{
    _drv.begin();
    _drv.setMode(DRV2605_MODE_INTTRIG); // internal trigger, listens for go() command
    _drv.selectLibrary(1);
}

void Vibration::setVibration(VIBRATION_MODE mode)
{
    if (mode == _currentVibrationMode)
        return;

    switch (mode)
    {
    case PULSE:
        _drv.setWaveform(0, 55);     // play effect
        _drv.setWaveform(1, 0);      // end waveform
        break;
    case BUZZ:
        _drv.setWaveform(0, 48);     // play effect
        _drv.setWaveform(1, 0);      // end waveform
        break;
    case HUMM:
        _drv.setWaveform(0, 119);    // play effect
        _drv.setWaveform(1, 0);      // end waveform
        break;
    default:
        break;
    }
}

void Vibration::start()
{
    _drv.go();
}

void Vibration::stop()
{
    _drv.stop();
}