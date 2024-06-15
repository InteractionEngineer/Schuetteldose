#include "LED.h"
#include "Touch.h"
#include "BMS.h"
#include "Force.h"
#include "Vibration.h"
#include "OSC.h"

LED switchLED(12);
Touch outerShell(A6);
BMS batteryManagement(A13, A12, A2);
Force appliedForce(A3);

// TODO: Initialisierung führt zu einem RTC (Real Time Clock) Watchdog Timer Fehler
Vibration hapticFeedback();
OSC oscHandler("WIFI_SSID", "WIFI_PWD", 8888, 9999, IPAddress(10, 40, 10, 105));

bool atStartup;

// controlled from outside (via OSC)
bool isFilled;

// controlled by loop
long lastBatteryMillis;
long lastPingMillis;

// constants
const int INTERVAL_BATTERY = 30 * 1000;
const int INTERVAL_PING = 1 * 1000;

void setup()
{
  Serial.begin(9600);

  isFilled = true;
  oscHandler.setup();
  atStartup = true;
}

void loop()
{
  transmitState();

  handleFeedback();

  if (appliedForce.measure() > 0 && outerShell.isTouched())
  {
    appliedForce.print();
  }

  if (appliedForce.measure() > 0 && !outerShell.isTouched())
  {
    outerShell.print();
  }

  // TODO: Das blockiert leider im Nachinein jede weitere Animation
  // if (atStartup)
  // {
  //     switchLED.pulse(3, 5, 30);
  //     atStartup = switchLED.isBusy; // false after animation is done and never resets
  // }

  // TODO: der trigger darf nicht die animation steuern! Es soll sie nur starten und stoppen. vllt so ähnlich wie setMode und go() --> der loop müsste an die LED klasse weitergegeben werden
  if (outerShell.isTouched())
    switchLED.flash(500);
}

void transmitState()
{
  if (millis() - lastBatteryMillis > INTERVAL_BATTERY)
  {
    oscHandler.sendCharge(batteryManagement.getVoltage());
    lastBatteryMillis = millis();
  }

  if (millis() - lastPingMillis > INTERVAL_PING)
  {
    oscHandler.ping();
    lastPingMillis = millis();
  }

  if (isFilled && outerShell.isTouched())
  {
    oscHandler.sendState(true, appliedForce.measure());
  }
}

void handleFeedback()
{
  if (outerShell.isTouched() && appliedForce.measure() > 0)
  {
    // hapticFeedback.setVibration(PULSE);
    // hapticFeedback.start();
  }
  else
  {
    // hapticFeedback.stop();
  }
}