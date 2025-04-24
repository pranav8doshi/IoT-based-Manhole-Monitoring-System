void setup() {
  pinMode(D5, OUTPUT);
}

void loop() {
  int notes[] = {262, 294, 330, 349, 392, 440, 494, 523};
  int duration = 100;

  for (int i = 0; i < 8; i++) {
    tone(D5, notes[i], duration);
    delay(duration);
    noTone(D5);
    delay(500);  // Small pause between notes
  }

 
  delay(1000);  // Pause between cycles
 for (int i = 7; i >=0; i--) {
    tone(D5, notes[i], duration);
    delay(duration);
   // noTone(D5);
    delay(500);  // Small pause between notes
  }


}
