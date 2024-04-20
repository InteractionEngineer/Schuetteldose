// Hardware: Disable LED and switch mode to low-power; optional: might need to be routed outsite (connect a toucpad / copper foil) -> everything connected is also sensitve - isolate!
// use pin D14, anticipate an active high whenever the touch-event is true

const int touchPin = 14; // Possible when WiFi is used?
const unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;
int lastTouchState = LOW;

bool readTouchSensor()
{
    int reading = digitalRead(touchPin);

    // If the reading has changed (i.e., the button state has changed), reset the debouncing timer
    if (reading != lastTouchState)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        // If the new button state has lasted for longer than the debounce delay, consider it the actual current state

        if (reading != lastTouchState)
        {
            lastTouchState = reading;

            if (reading == HIGH)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    // Save the reading. Next time through the loop, it'll be the lastButtonState:
    lastTouchState = reading;
    return false;
}