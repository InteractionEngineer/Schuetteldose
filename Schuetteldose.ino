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

  drv.begin();
  drv.setMode(DRV2605_MODE_INTTRIG);  // internal trigger, listens for go() command
  drv.selectLibrary(1);

  isFilled = true;
  lastPingMillis = millis();
  lastBatteryMillis = millis();

  oscHandler.setup();
}

void loop() {
  // TODO: muss die message jeden Loop neu instantiiert werden? Kommen überhaupt alle Daten innerhalb eines Loops?
  // OSCMessage msg1("/test");
  // msg1.dispatch("/test", oscReceiveWrapper);

  int force = appliedForce.measure();
  bool touched = housing.isTouched();
  float voltage = batteryManagement.getVoltage();

  transmitState(force, touched);
  handleFeedback(force);
  sendPing();
  checkBattery(voltage);
  handleCharging(voltage);
  switchLED.handleState();
}

void oscReceiveWrapper(OSCMessage &msg) {
  oscHandler.receive(msg);
  // TODO: boolean isFilled manipulieren
}

void sendPing() {
  if (millis() - lastPingMillis > INTERVAL_PING) {
    oscHandler.ping();
    lastPingMillis = millis();
  }
}

void checkBattery(float voltage) {
  if (millis() - lastBatteryMillis > INTERVAL_BATTERY) {
    oscHandler.sendCharge(voltage);
    if (voltage < 3) switchLED.pulse(30, 1);
    lastBatteryMillis = millis();
  }
}

void handleCharging(float voltage) {
  if (voltage < 3.8 && batteryManagement.isCharging()) switchLED.pulse(1, 1);
  else if (voltage >= 3.8 && batteryManagement.isCharging()) switchLED.pulse(5, 10);
}

void transmitState(int force, bool touched) {
  // TODO: Massefehler, wenn Dose ohne Stromanschluss: Zu geringe Differenz, um Sensor auszulösen (?)
  oscHandler.sendState(touched, force);
}

void handleFeedback(int force) {
  if (force > 0 && isFilled) {
    if (force == 1) hapticFeedback.setVibration(SPRAY_LIGHT);
    else if (force == 2) hapticFeedback.setVibration(SPRAY_MEDIUM);
    else if (force == 3) hapticFeedback.setVibration(SPRAY_STRONG);
    else if (force >= 4) hapticFeedback.setVibration(SPRAY_MAX);
    else Serial.println("ERROR: There is a problem measuring the appliedForce.");
  } else return;

  hapticFeedback.start();
}