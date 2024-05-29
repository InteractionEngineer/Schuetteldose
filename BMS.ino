// die halbe Spannung lässt sich über den Pin A13 / GPIO 35 abrufen -- dieser Pin existiert nur intern!
// Temperatur überwachen, NTC an A2 / GPIO 34

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    // Aktuell nur lesen der Werte, keine Verarbeitung. Dient zur Überprüfung der Funktionalität.
    int voltage = analogRead(A13);
    int temperature = analogRead(A2);

    Serial.print("Voltage: ");
    Serial.println(voltage);
    Serial.print("Temperature: ");
    Serial.println(temperature);

    delay(1000);
}