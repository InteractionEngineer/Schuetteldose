#ifndef LED_H
#define LED_H

#include <Arduino.h>

// Define the states for the state machine
enum LEDState {
  IDLE,
  PULSING,
  FLASHING,
  TURNING_OFF
};

class LED {
public:
  LED(int ledPin);
  void turnOff();
  void handleState();

  void pulse(int, int, int);
  void pulse(int, int);

  void flash(int, int);
  void flash(int);

private:
  int _pin;
  bool _ledState;
  unsigned long _previousMillis;
  LEDState _state;

  // pulsing
  int _brightness;
  int _fadeAmount;
  int _pulseInterval;
  int _pulseCount;
  int _targetPulseCount;

  // flashing
  int _flashInterval;
  int _flashCount;
  int _targetFlashCount;

  void _resetPulseAnimation(int, int, int);
  void _resetFlashAnimation(int, int);
  void _actuallyFlash(unsigned long);
  void _actuallyPulse(unsigned long);
};

#endif  // LED_H
