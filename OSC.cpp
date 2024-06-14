#include "OSC.h"

OSC::OSC(const char* ssid, const char* pass, const IPAddress& outIp, unsigned int outPort, unsigned int localPort)
    : _ssid(ssid), _pass(pass), _outIp(outIp), _outPort(outPort), _localPort(localPort)
{
    _routeState = "/sprayar/microcontroller/state";
    _routePing = "/sprayar/microcontroller/ping";
    _routeCharge = "/sprayar/microcontroller/charge";
}

void OSC::setup()
{
    // Connect to WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(_ssid.c_str());
    WiFi.begin(_ssid.c_str(), _pass.c_str());

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500); // TODO: change to millis
        Serial.print(".");
    }
    Serial.println("");

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Starting UDP");
    _Udp.begin(_localPort);
    Serial.print("Local port: ");
    Serial.println(_localPort);
}

void OSC::receive()
{
    // OSCMessage msg;
    // int size = _Udp.parsePacket();

    // if (size > 0)
    // {
    //     while (size--)
    //     {
    //         msg.fill(_Udp.read());
    //     }
    //     if (!msg.hasError())
    //     {
    //         msg.dispatch("/led", led); // You need to implement the `led` function
    //     }
    //     else
    //     {
    //         _error = msg.getError();
    //         Serial.print("error: ");
    //         Serial.println(_error);
    //     }
    // }
}

void OSC::send(const char* route, const char* message)
{
    OSCMessage msg(route);
    msg.add(message);
    _Udp.beginPacket(_outIp, _outPort);
    msg.send(_Udp);
    _Udp.endPacket();
    msg.empty();
}

void OSC::ping()
{
    send(_routePing, "PING");
}

void OSC::sendCharge(float charge)
{
    // TODO: float richtig umwandeln
    send(_routeCharge, charge < 3.5 ? "LOW" : "OK");
}

void OSC::sendState(bool isGrabbed, int appliedForce)
{
    // TODO: int richtig umwandeln
    send(_routeState, isGrabbed ? "GRABBED" : "RELEASED");
}