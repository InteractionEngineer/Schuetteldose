#ifndef OSC_H
#define OSC_H

#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include "LED.h"

#include <string>

class OSC {
public:
  OSC(const char* ssid, const char* pass, const IPAddress& outIp, unsigned int outPort, unsigned int localPort);
  void setup(LED *ledInstance);
  void receive(OSCMessage& msg);
  void send(OSCMessage& msg);
  void sendState(bool isGrabbed, int32_t appliedForce);
  void ping();
  void sendCharge(float charge);

private:
  WiFiUDP _Udp;
  std::string _ssid;
  std::string _pass;
  IPAddress _outIp;
  unsigned int _outPort;
  unsigned int _localPort;
  unsigned long _previousMillis;

  const char* _routeState;
  const char* _routePing;
  const char* _routeCharge;

  OSCErrorCode _error;
};

#endif  // OSC_H
