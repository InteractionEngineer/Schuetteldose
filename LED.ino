// at pin D12
// use for any kind of system-feedback to the user, eg: charging, on/off, error

int ledPin = 12;

void setup()
{
    // LED is connected to pin D12
    pinMode(ledPin, OUTPUT);
}

void loop()
{
    // Turn the LED on
    digitalWrite(ledPin, HIGH);
    delay(1000);
    // Turn the LED off
    digitalWrite(ledPin, LOW);
    delay(1000);
}