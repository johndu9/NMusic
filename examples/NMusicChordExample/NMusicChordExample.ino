#include <NMusic.h>

int** chords;  //this will store our chords
int* notes;  //this will store our scale
int chord = 0;  //this will store the current chord
int note = 0;  //this will store the current note in the chord

void setup() {
  pinMode(8, OUTPUT);  //we'll put our speaker on pin 8
  notes = NMusic::getScale(3, true);  //puts a D# major scale into notes
  chords = new int*[4];  //allocate some room for our chords
  chords[0] = NMusic::getChord(notes, 0, true, 0);  //I chord going up (D#, G, A#)
  chords[1] = NMusic::getChord(notes, 3, true, 0);  //IV chord going up (G#, B#, D#)
  chords[2] = NMusic::getChord(notes, 4, false, 0);  //V chord going down (E#, D, A#)
  chords[3] = NMusic::getChord(notes, 3, false, 0);  //IV chord going down (D#, B#, G#)
}

void loop() {
  float frequency = NMusic::getFrequency(chords[chord][note]);  //stores frequency of the current note on the current chord
  tone(8, frequency);  //plays that frequency on pin 8
  delay(1000);  //we want to play each note for a second
  note = (note + 1) % 3;  //"loop" note from 0 to 2
  chord = (chord + !note) % 4;  //"loop" chord from 0 to 3 if note is 0
}
