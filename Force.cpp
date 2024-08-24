#include "Force.h"

Force::Force(int forcePin) {
  _pin = forcePin;
  pinMode(_pin, INPUT);
}

int Force::measure() {
  float fsrVoltage_MV = analogRead(_pin);
  if (fsrVoltage_MV == 0) return 0;

  int fsrResistance = 3300 - fsrVoltage_MV;
  fsrResistance *= 10000;  // 10K resistor in voltage divider
  fsrResistance /= fsrVoltage_MV;

  int fsrConductance = 1000000;  // 1M ohm (from documentation)
  fsrConductance /= fsrResistance;
  int fsrForce;

  fsrForce = fsrConductance / 15;  // bring observed values to 0-10 range

  return fsrForce < 0 ? 0 : fsrForce;
}

void Force::print() {
  int force = measure();
  if (force > 0) {
    Serial.print("Approximated force in Newtons: ");
    Serial.println(force);
  }
}