const int analogPin = A0;
const int ledCount = 9;
int ledPins[] = {2,3,4,5,6,7,8,9,10};

void setup() {
  // Set all LED pins to output mode
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }
}

void loop() {
  int sensorReading = analogRead(analogPin);

  // Re-map the analogue pin values (0-1023) to the range of pins (0-9)
  // and return the revised sensorReading as the current LED level
  int ledLevel = map(sensorReading, 0, 1023, 0, ledCount);

  // Check each LED in turn
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    if (thisLed < ledLevel) {
      digitalWrite(ledPins[thisLed], HIGH); // If the LED is below the max level, turn it on
    } else {
      digitalWrite(ledPins[thisLed], LOW); // Otherwise turn it off
    }
  }
}
