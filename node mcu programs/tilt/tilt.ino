const int TILT_PIN = 6;  // Tilt sensor pin
const int LED_PIN = 13;   // LED pin

void setup() {
  pinMode(TILT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int tiltValue = digitalRead(TILT_PIN);
Serial.println("Tilt low!");
  if (tiltValue == LOW) {
    Serial.println("Tilt Detected!");
    digitalWrite(LED_PIN, HIGH);  // Turn on the LED
  } else {
    digitalWrite(LED_PIN, LOW);   // Turn off the LED
  }

  delay(100);  // Adjust the delay as needed for debouncing or responsiveness
}
