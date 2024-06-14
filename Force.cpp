#include "Force.h"

Force::Force(int forcePin)
{
    _pin = forcePin;
    pinMode(_pin, INPUT);
}

int Force::measure()
{
    float fsrVoltage_MV = analogRead(_pin);
    if (fsrVoltage_MV == 0)
        return 0;

    int fsrResistance = 3300 - fsrVoltage_MV;
    fsrResistance *= 10000; // 10K resistor in voltage divider
    fsrResistance /= fsrVoltage_MV;

    int fsrConductance = 1000000; // 1M ohm (from documentation)
    fsrConductance /= fsrResistance;
    int fsrForce;

    if (fsrConductance <= 1000) // force-curve 1 (from documentation)
        fsrForce = fsrConductance / 80;
    else // force-curve 2 (from documentation)
    {
        fsrForce = fsrConductance - 1000;
        fsrForce /= 30;
    }

    return fsrForce;
}

void Force::print()
{
    Serial.print("Approximated force in Newtons: ");
    Serial.println(measure());
}