#include "LED.h"

LED::LED(int ledPin) {
  _pin = ledPin;
  pinMode(_pin, OUTPUT);

  _state = IDLE;
  _pulseCount = 0;
  _targetPulseCount = 0;
  _previousMillis = 0;
  _pulseInterval = 0;
  _fadeAmount = 0;
  _brightness = 0;

  analogWrite(_pin, _brightness);
}

LEDAnimationState LED::getState() {
  return _state;
}

void LED::pulse(int times, int fadeAmount, int pulseInterval) {
  if (_state == IDLE) {
    _resetPulseAnimation(times, fadeAmount, pulseInterval);
    _state = PULSING;
  }

  handleState();
}

void LED::pulse(int fadeAmount, int pulseInterval) {
  pulse(1, fadeAmount, pulseInterval);
}

void LED::_resetPulseAnimation(int times, int fadeAmount, int pulseInterval) {
  _targetPulseCount = times;
  _pulseCount = 0;
  _previousMillis = millis();
  _brightness = 0;
  _fadeAmount = fadeAmount;
  _pulseInterval = pulseInterval;
  analogWrite(_pin, _brightness);
}

void LED::handleState() {
  unsigned long currentMillis = millis();

  switch (_state) {
    case PULSING:
      if (_pulseCount < _targetPulseCount) {
        if (currentMillis - _previousMillis >= _pulseInterval) {
          _actuallyPulse(currentMillis);
        }
      } else {
        _state = TURNING_OFF;
      }
      break;

    case TURNING_OFF:
      turnOff();
      _state = IDLE;
      break;

    case IDLE:
    default:
      if (_brightness < 255) {
        _brightness++;
        analogWrite(_pin, _brightness);
      }
      break;
  }
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
  _brightness = 0;
  _targetPulseCount = 0;
  analogWrite(_pin, _brightness);
}