// TODO: needs to be transformed to a proper class

#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>

// TODO: Change to network credentials!

char ssid[] = "*****************"; // your network SSID (name)
char pass[] = "*******";           // your network password

WiFiUDP Udp;                            // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(10, 40, 10, 105); // remote IP of your computer
const unsigned int outPort = 9999;      // remote port to receive OSC
const unsigned int localPort = 8888;    // local port to listen for OSC packets (actually not used for sending)

// Osc Routes - OUTGOING
const char *routeSprayCanState = "/sprayar/microcontroller/state";
const char *routePing = "/sprayar/microcontroller/ping";
const char *routeSprayCanCharge = "/sprayar/microcontroller/charge";

OSCErrorCode error;

void setup()
{
  setupOSC();
}

void loop()
{
  sendSprayCanState();
  sendPing();
  sendSprayCanCharge();
  delay(1000);
}

void setupOSC()
{
  Serial.begin(115200);

  // Connect to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(localPort);
}

// void receiveOSC()
// {
//   OSCMessage msg;
//   int size = Udp.parsePacket();

//   if (size > 0)
//   {
//     while (size--)
//     {
//       msg.fill(Udp.read());
//     }
//     if (!msg.hasError())
//     {
//       msg.dispatch("/led", led);
//     }
//     else
//     {
//       error = msg.getError();
//       Serial.print("error: ");
//       Serial.println(error);
//     }
//   }
// }

void sendOSC()
{
  OSCMessage msg("/test");
  msg.add("hello, osc.");
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
}

void sendSprayCanState()
{
  if (!isGrabbed)
  {
    return;
  }

  OSCMessage msg(routeSprayCanState);

  // Is Spray Can in hand?
  if (isGrabbed)
  {
    msg.add(true);
  }
  else
  {
    msg.add(false);
  }
  // Is spraying button pressed?
  if (mappedForce > 0)
  {
    msg.add(mappedForce);
  }
  else
  {
    msg.add(0);
  }

  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
}

void sendPing()
{
  OSCMessage msg(routePing);
  msg.add("PING");
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
}

void sendSprayCanCharge()
{
  // TODO: Implement BMS functionality first
}