#ifndef LED_H
#define LED_H

#include <Arduino.h>

// Define the states for the state machine
enum LEDAnimationState {
  IDLE,
  PULSING,
  // FLASHING,
  TURNING_OFF
};

// TODO: Der Wechsel von Pulse zu Flash führt immer dazu, dass die LED dauerhaft bleibt dunkel
class LED {
public:
  LED(int ledPin);
  void turnOff();
  void handleState();
  LEDAnimationState getState();

  void pulse(int times, int fadeAmount, int pulseInterval);
  void pulse(int fadeAmount, int pulseInterval);

  // void flash(int times, int duration_ms);
  // void flash(int duration_ms);

private:
  int _pin;
  // bool _ledState; // TODO: könnte der Grund für den Konflikt zwischen Flash und Pulse sein -> Boolean! (brightness beim analogen Schreiben hat 256 Werte)
  unsigned long _previousMillis;
  LEDAnimationState _state;

  // pulsing
  int _brightness;
  int _fadeAmount;
  int _pulseInterval;
  int _pulseCount;
  int _targetPulseCount;

  // flashing
  // int _flashInterval;
  // int _flashCount;
  // int _targetFlashCount;

  void _resetPulseAnimation(int times, int fadeAmount, int pulseInterval);
  // void _resetFlashAnimation(int times, int duration_ms);
  // void _actuallyFlash(unsigned long currentMillis);
  void _actuallyPulse(unsigned long currentMillis);
};

#endif  // LED_H
