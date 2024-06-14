#ifndef LED_H
#define LED_H

#include <Arduino.h>
class LED {
  public:
    LED(int pin);
    void pulse(int, int, int);
    void pulse(int, int);
    void flash(int, int);
    void flash(int);
    void turnOff();
    bool isBusy;
  private:
    void _resetAnimation(int, int, unsigned long);
    void _resetAnimation(int, int, int, unsigned long);
    void _actuallyFlash(unsigned long);
    void _actuallyPulse(unsigned long);
    int _pin;
    int _flashCount;
    int _targetFlashCount;
    int _pulseCount;
    int _targetPulseCount;
    unsigned long _previousMillis;
    int _state;
    unsigned long _flashInterval;
    unsigned long _pulseInterval;
    int _fadeAmount;
    int _brightness;
    bool _terminate;
};

#endif /* LED_H */
