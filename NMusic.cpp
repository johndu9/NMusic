/**
	NMusic.cpp - Simple music library
	@author John Du
*/

#include "Arduino.h"
#include "NMusic.h"

/**
	For implementation inspiration see: http://en.wikipedia.org/wiki/Scale_(music)
	@param note Half-steps from middle C to scale key
	@param major Whether or not the scale is major
	@return Returns int array of size 8 that has the notes for the scale
*/
int* NMusic::getScale(int note, boolean major) {
	int* base = new int[8];
	int firstSemitone = 1 + major * 1;
	int secondSemitone = 4 + major * 2;
	for (int i = 0; i < 8; i++) {
		base[i] = note + i * 2;
		if (i > firstSemitone) {
			base[i]--;
			if (i > secondSemitone) {
				base[i]--;
			}
		}
	}
	return base;
}

/**
	For implementation inspiration see: http://en.wikipedia.org/wiki/C_(musical_note)#Middle_C and http://www.phy.mtu.edu/~suits/NoteFreqCalcs.html
	@param note Half-steps from middle C
	@return Returns frequency of the given note
*/
float NMusic::getFrequency(int note) {
	return 262.0f * pow((pow(2.0f, 1.0f / 12.0f)), (note));
}

/**
	Array version of getFrequency(int note), useful for calculating frequencies before runtime instead of during
	@param notes Half-steps from middle C
	@return Returns frequencies of the given notes
*/
float* NMusic::getFrequency(int notes[]) {
	int size = sizeof(notes) / sizeof(int);
	float* base = new float[size];
	for (int i = 0; i < size; i++) {
		base[i] = getFrequency(notes[i]);
	}
	return base;
}

/**
	For implementation inspiration see: http://en.wikipedia.org/wiki/Triad_(music)
	@param scale The scale from which we pull notes for the chord
	@param scaleDegree Degree of chord (0 index, so chord degree I -> 0, degree ii -> 1, etc.); see: http://en.wikipedia.org/wiki/Degree_(music)
	@param up Whether the chord is ordered up or down
	@param inverts Times to invert chord (placing lowest note on top); see: http://en.wikipedia.org/wiki/Inversion_(music)#Inversions
	@return Returns the chord that fits these properties
*/
int* NMusic::getChord(int scale[], int scaleDegree, boolean up, int inverts) {
	int* base = new int[3];
	int chordNotes[] = {(4 * !up) + scaleDegree, 2 + scaleDegree, (4 * up) + scaleDegree};
	boolean octaveUp[] = {0, 0, 0};
	for (int i = 0; i < 3; i++) {
		int over = chordNotes[i] % 7;
		base[i] = scale[over];
		if(over != chordNotes[i]){
			base[i] = base[i] + 12;
		}
	}
	for (int i = 0; i < inverts; i++) {
		invertChord(base, up);
	}
	return base;
}

/**
	For implementation inspiration see: http://en.wikipedia.org/wiki/Inversion_(music)#Inversions
	@param base Chord to invert
	@param up Whether the chord is going up or down
*/
void NMusic::invertChord(int base[], boolean up) {
	int chordNotes[3];
	if (up) {
		chordNotes[0] = base[1];
		chordNotes[1] = base[2];
		chordNotes[2] = base[0] + 12;
	} else {
		chordNotes[0] = base[2] + 12;
		chordNotes[1] = base[0];
		chordNotes[2] = base[1];
	}
	for (int i = 0; i < 3; i++) {
		base[i] = chordNotes[i];
	}
}