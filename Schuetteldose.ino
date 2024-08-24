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
BMS batteryManagement(A13, A4, A2);
Force appliedForce(A3);
Adafruit_DRV2605 drv;
Vibration hapticFeedback(&drv);
OSC oscHandler(WIFI_SSID, WIFI_PWD, PARTNER_IP, 8888, 9999);

// controlled from outside (via OSC)
bool isFilled;
bool refilling;

// controlled by loop
long lastBatteryMillis;
long lastPingMillis;

// constants
const int INTERVAL_BATTERY = 30 * 1000;
const int INTERVAL_PING = 1 * 1000;

void setup() {
  Serial.begin(115200);

  drv.begin();
  drv.setMode(DRV2605_MODE_INTTRIG);  // internal trigger, listens for go() command
  drv.selectLibrary(1);

  isFilled = true;
  refilling = false;
  lastPingMillis = millis();
  lastBatteryMillis = millis();

  oscHandler.setup(&switchLED);
}

void loop() {
  int force = appliedForce.measure();
  bool touched = housing.isTouched();
  float voltage = batteryManagement.getVoltage();

  transmitState(force, touched);
  handleFeedback(force);
  sendPing();
  checkBattery(voltage);
  handleCharging(voltage);
  switchLED.handleState();
  oscReceiveWrapper();
}

void oscReceiveWrapper() {
  OSCMessage msg;
  oscHandler.receive(msg);
  if (!msg.hasError()) {
    msg.dispatch(
      "/sprayar/microcontroller/Refill/Start", startRefill);
    msg.dispatch(
      "/sprayar/microcontroller/Refill/Stop", stopRefill);
    msg.dispatch(
      "/sprayar/microcontroller/FillState/Full", setFull);
    msg.dispatch(
      "/sprayar/microcontroller/FillState/Empty", setEmpty);
  }
}

void startRefill(OSCMessage&) {
  refilling = true;
}
void stopRefill(OSCMessage&) {
  refilling = false;
}
void setFull(OSCMessage&) {
  isFilled = true;
}
void setEmpty(OSCMessage&) {
  isFilled = false;
}

void sendPing() {
  if (millis() - lastPingMillis > INTERVAL_PING) {
    oscHandler.ping();
    lastPingMillis = millis();
  }
}

void checkBattery(float voltage) {
  if (millis() - lastBatteryMillis > INTERVAL_BATTERY) {
    float thermistorR = batteryManagement.readThermistor();
    oscHandler.sendCharge(voltage);
    if (voltage < 3.5) switchLED.pulse(3, 1);         // low battery
    if (thermistorR > 25000) switchLED.pulse(30, 1);  // battery too hot
    lastBatteryMillis = millis();
  }
}

void handleCharging(float voltage) {
  if (batteryManagement.isCharging()) {
    if (voltage > 4.3) switchLED.pulse(1, 1);  // Error: Plugged in but no connection to battery
    else switchLED.pulse(5, 40);               // Charging
  }
}

void transmitState(int force, bool touched) {
  int mappedForce;

  if (force > 9)
    mappedForce = 3;
  else if (force > 5)
    mappedForce = 2;
  else if (force > 0)
    mappedForce = 1;
  else mappedForce = 0;

  oscHandler.sendState(touched, mappedForce);
}

void handleFeedback(int force) {
  if (force > 0 && isFilled) {
    if (force == 1) hapticFeedback.setVibration(JUMPSTART);
    else if (force == 2) hapticFeedback.setVibration(SPRAY_LIGHT);
    else if (force < 5) hapticFeedback.setVibration(SPRAY_MEDIUM);
    else if (force < 9) hapticFeedback.setVibration(SPRAY_STRONG);
    else if (force >= 9) hapticFeedback.setVibration(SPRAY_MAX);
    else Serial.println("ERROR: There is a problem measuring the appliedForce.");
  } else if (refilling) {
    hapticFeedback.setVibration(FILL);
  } else return;

  hapticFeedback.start();
}