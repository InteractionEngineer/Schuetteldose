#include "LED.h"

LED::LED(int ledPin) {
  _pin = ledPin;
  pinMode(_pin, OUTPUT);

  isBusy = false;
  
  _flashCount = 0;
  _targetFlashCount = 0;
  _pulseCount = 0;
  _targetPulseCount = 0;
  _previousMillis = 0;
  _state = 0; // same as LOW
  _flashInterval = 0;
  _pulseInterval = 0;
  _fadeAmount = 0;
  _brightness = 0;
  _terminate = false;

  digitalWrite(_pin, _state);
}

void LED::pulse(int times, int fadeAmount, int pulseInterval) {
  unsigned long currentPulseMillis = millis();

  if (_targetPulseCount != times && !isBusy) _resetAnimation(times, fadeAmount, pulseInterval, currentPulseMillis);

  if (!_terminate && _pulseCount < _targetPulseCount) {
    if (currentPulseMillis - _previousMillis >= _pulseInterval) {
      _actuallyPulse(currentPulseMillis);
    }
  } else if (_pulseCount >= _targetPulseCount) {
    turnOff();
  }
}

void LED::pulse(int fadeAmount, int pulseInterval) {
  pulse(1, fadeAmount, pulseInterval);
}

void LED::flash(int times, int duration_ms) {
  unsigned long currentFlashMillis = millis();

  if (_targetFlashCount != times && !isBusy) _resetAnimation(times, duration_ms, currentFlashMillis);

  if (!_terminate && _flashCount < _targetFlashCount * 2) {
    if (currentFlashMillis - _previousMillis >= _flashInterval) {
      _actuallyFlash(currentFlashMillis);
    }
  } else if (_flashCount >= _targetFlashCount * 2) {
    turnOff();
  }
}

void LED::flash(int duration_ms) {
  flash(1, duration_ms);
}

void LED::_resetAnimation(int times, int duration_ms, unsigned long currentMillis) {
  _targetFlashCount = times;
  _flashCount = 0;
  _previousMillis = currentMillis;
  _state = LOW;
  _flashInterval = duration_ms;
  digitalWrite(_pin, _state);
  _terminate = false;
  isBusy = true;
}

void LED::_resetAnimation(int times, int fadeAmount, int pulseInterval, unsigned long currentMillis) {
  _targetPulseCount = times;
  _pulseCount = 0;
  _previousMillis = currentMillis;
  _state = 0;
  _fadeAmount = fadeAmount;
  _pulseInterval = pulseInterval;
  analogWrite(_pin, _state);
  _terminate = false;
  isBusy = true;
}

void LED::_actuallyFlash(unsigned long currentMillis) {
  _previousMillis = currentMillis;
  _state = !_state;
  _flashCount++;
  digitalWrite(_pin, _state);
}

void LED::_actuallyPulse(unsigned long currentMillis) {
  _previousMillis = currentMillis;
  _brightness += _fadeAmount;
  if (_brightness <= 0 || _brightness >= 255) {
    _fadeAmount = -_fadeAmount;
    if (_brightness <= 0) {
      _pulseCount++;
    }
  }
  analogWrite(_pin, _brightness);
}

void LED::turnOff() {
  _terminate = true;
  _brightness = 0;
  _targetPulseCount = 0;
  _targetFlashCount = 0;
  digitalWrite(_pin, LOW);
  isBusy = false;
}
