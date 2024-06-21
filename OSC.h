#ifndef OSC_H
#define OSC_H

#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>

#include <string>

class OSC
{
public:
    OSC(const char* , const char*, const IPAddress&, unsigned int, unsigned int);
    void setup();
    void receive(OSCMessage&);
    void send(OSCMessage&);
    void sendState(bool, int32_t);
    void ping();
    void sendCharge(float);

private:
    WiFiUDP _Udp;
    std::string _ssid;
    std::string _pass;
    IPAddress _outIp;
    unsigned int _outPort;
    unsigned int _localPort;

    const char* _routeState;
    const char* _routePing;
    const char* _routeCharge;

    OSCErrorCode _error;
};

#endif // OSC_H
