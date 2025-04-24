
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(D1, OUTPUT);  
  pinMode(D3, OUTPUT);
  pinMode(D5, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(D1, HIGH); 
  delay(4000);
  digitalWrite(D1, LOW);
  digitalWrite(D3, HIGH); 
  delay(2000);
  digitalWrite(D3, LOW);
  digitalWrite(D5, HIGH);
  delay(4000);
  digitalWrite(D5, LOW);
  digitalWrite(D3, HIGH); 
  delay(2000);
  digitalWrite(D3, LOW);
}
