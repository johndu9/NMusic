#include <NMusic.h>

int* notes;  //this will store our scale
int note = 0;  //this will store the current note scale

void setup() {
  pinMode(8, OUTPUT);  //we'll put our speaker on pin 8
  notes = NMusic::getScale(0, true);  //puts a C major scale into notes
}

void loop() {
  float frequency = NMusic::getFrequency(notes[note]);  //stores frequency of the current note on the scale
  tone(8, frequency);  //plays that frequency on pin 8
  delay(1000);  //we want to play each note for a second
  note = (note + 1) % 8;  //"loop" note from 0 to 7
}
