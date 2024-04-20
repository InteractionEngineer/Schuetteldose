// TODO: Change from 5V to 3.3V and modify Pins according to wiring diagram

/* FSR testing sketch.

Connect one end of FSR to power, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground

For more information see www.ladyada.net/learn/sensors/fsr.html */

int fsrPin = 0;              // the FSR and 10K pulldown are connected to a0
int fsrReading;              // the analog reading from the FSR resistor divider
int fsrVoltage;              // the analog reading converted to voltage
unsigned long fsrResistance; // The voltage converted to resistance, can be very big so make "long"
unsigned long fsrConductance;
long fsrForce; // Finally, the resistance converted to force
int mappedForce;

// void setup(void)
// {
//   Serial.begin(9600); // We'll send debugging information via the Serial monitor
// }

// void loop(void)
// {
//   fsrReading = analogRead(fsrPin);
//   Serial.print("Analog reading = ");
//   Serial.println(fsrReading);

//   // analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 5000mV)
//   fsrVoltage = map(fsrReading, 0, 1023, 0, 3300);
//   Serial.print("Voltage reading in mV = ");
//   Serial.println(fsrVoltage);

//   if (fsrVoltage == 0)
//   {
//     Serial.println("No pressure");
//   }
//   else
//   {
//     // The voltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V
//     // so FSR = ((Vcc - V) * R) / V        yay math!
//     fsrResistance = 3300 - fsrVoltage; // fsrVoltage is in millivolts so 5V = 5000mV
//     fsrResistance *= 10000;            // 10K resistor
//     fsrResistance /= fsrVoltage;
//     Serial.print("FSR resistance in ohms = ");
//     Serial.println(fsrResistance);

//     fsrConductance = 1000000; // we measure in micromhos so
//     fsrConductance /= fsrResistance;
//     Serial.print("Conductance in microMhos: ");
//     Serial.println(fsrConductance);

//     // Use the two FSR guide graphs to approximate the force
//     if (fsrConductance <= 1000)
//     {
//       fsrForce = fsrConductance / 80;
//       Serial.print("Force in Newtons: ");
//       Serial.println(fsrForce);
//     }
//     else
//     {
//       fsrForce = fsrConductance - 1000;
//       fsrForce /= 30;
//       Serial.print("Force in Newtons: ");
//       Serial.println(fsrForce);
//     }
//   }
//   Serial.println("--------------------");
//   delay(1000);
// }

void measureForce()
{
  fsrReading = analogRead(fsrPin);
  fsrVoltage = map(fsrReading, 0, 1023, 0, 3300);

  // TODO: Find correct voltage for inactive threshold

  if (fsrVoltage <= 0.1)
  {
    fsrForce = 0;
    mappedForce = 0;
    return;
  }
  else
  {
    fsrResistance = 3300 - fsrVoltage;
    fsrResistance *= 10000;
    fsrResistance /= fsrVoltage;
    fsrConductance = 1000000;
    fsrConductance /= fsrResistance;
    if (fsrConductance <= 1000)
    {
      fsrForce = fsrConductance / 80;

      // Map force to 0 - 10
      // TODO: Check if 100N is actual upper limit
      mappedForce = map(fsrForce, 0, 100, 0, 10);
    }
    else
    {
      fsrForce = fsrConductance - 1000;
      fsrForce /= 30;

      // Map force to 0 - 10
      // TODO: Check if 100N is actual upper limit
      mappedForce = map(fsrForce, 0, 100, 0, 10);
    }
  }
}

/**
 * It is possible to calculate the actual resistance from the reading but unfortunately,
 * variations in the IDE and arduino board will make it inconsistant.
 * Be aware of that if you change IDE versions of OS's, or use a 3.3V arduino instead of 5V,
 * or change from a 16mhz Arduino to a 8Mhz one (like a lilypad) there may be differences
 * due to how long it takes to read the value of a pin. Usually that isn't a big deal but
 * it can make your project hard to debug if you aren't expecting it!
 */
