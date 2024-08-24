#include "Touch.h"

Touch::Touch(int touchPin) {
  _pin = touchPin;
  pinMode(_pin, INPUT);
}

bool Touch::isTouched() {
  return digitalRead(_pin);
}

void Touch::print() {
  Serial.print("Touch sensor is ");
  Serial.println(isTouched() ? "touched" : "not touched");
}