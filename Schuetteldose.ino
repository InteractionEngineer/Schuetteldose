// imports

// controlled by OSC
bool isFilled;
bool isGrabbed;

// controlled by loop
long lastBatteryMillis;
long lastPingMillis;

// constants
const int INTERVAL_BATTERY = 30 * 1000;
const int INTERVAL_PING = 1 * 1000;

void setup()
{
  isFilled = true;
  isGrabbed = false;
  setupOSC();
}

void loop()
{
  // temporary variables
  unsigned long currentMillis = millis();

  isGrabbed = readTouchSensor();
  // send battery
  if (currentMillis - lastBatteryMillis > INTERVAL_BATTERY)
  {
    // check battery
    lastBatteryMillis = currentMillis;
  }

  // send ping
  if (currentMillis - lastPingMillis > INTERVAL_PING)
  {
    // check ping
    sendPing();
    lastPingMillis = currentMillis;
  }

  // provide feedback when spraying
  if (isFilled && isGrabbed)
  {
    // spray
  }
}
