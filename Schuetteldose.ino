#include "LED.h"
#include "Touch.h"
#include "BMS.h"
#include "Force.h"
#include "Vibration.h"
#include "Adafruit_DRV2605.h"
#include "OSC.h"
#include "Credentials.h"

LED switchLED(12);
Touch housing(A6);
BMS batteryManagement(A13, A12, A2);
Force appliedForce(A3);
Adafruit_DRV2605 drv;
Vibration hapticFeedback(&drv);
OSC oscHandler(WIFI_SSID, WIFI_PWD, PARTNER_IP, 8888, 9999);

bool atStartup;

// controlled from outside (via OSC)
bool isFilled;

// controlled by loop
long lastBatteryMillis;
long lastPingMillis;

// constants
const int INTERVAL_BATTERY = 30 * 1000;
const int INTERVAL_PING = 1 * 1000;

void setup() {
  switchLED.pulse(3, 5, 30);

  Serial.begin(115200);
  delay(2000); // time to initialze

  drv.begin();
  drv.setMode(DRV2605_MODE_INTTRIG);  // internal trigger, listens for go() command
  drv.selectLibrary(1);

  isFilled = true;
  atStartup = true;
  lastPingMillis = millis();
  lastBatteryMillis = millis();

  oscHandler.setup();
}

void loop() {
  OSCMessage msg1("/test");
  msg1.dispatch("/test", oscReceiveWrapper);

  transmitState();
  handleFeedback();

  // TODO: Der Wechsel von Pulse zu Flash funktioniert nicht, die LED bleibt dunkel
  if (housing.isTouched()) switchLED.flash(500);
  switchLED.handleState();
}

void oscReceiveWrapper(OSCMessage &msg) {
  oscHandler.receive(msg);
}

void transmitState() {
  if (millis() - lastBatteryMillis > INTERVAL_BATTERY) {
    oscHandler.sendCharge(batteryManagement.getVoltage());
    lastBatteryMillis = millis();
  }

  if (millis() - lastPingMillis > INTERVAL_PING) {
    oscHandler.ping();
    lastPingMillis = millis();
  }

  if (isFilled && housing.isTouched()) {
    oscHandler.sendState(true, appliedForce.measure());
  }
}

void handleFeedback() {
  if (housing.isTouched() && appliedForce.measure() > 0) {
    hapticFeedback.setVibration(BUZZ);
    hapticFeedback.start();
  }
}