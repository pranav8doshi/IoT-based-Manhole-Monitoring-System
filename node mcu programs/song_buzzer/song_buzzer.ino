// Melody notes and durations
int melody[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
};

int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 4
};

void setup() {
  // Set the pin for the speaker
  int speakerPin = 8;
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  // Iterate through the melody array
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    int noteDuration = 1000 / noteDurations[i];
    tone(8, melody[i], noteDuration);
    delay(noteDuration * 1.3); // Add a small delay between notes
    noTone(8);
  }
}
