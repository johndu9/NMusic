/**
  NMusic.h - Simple music library
  @author John Du
*/
#ifndef NMusic_h
	#define NMusic_h
	#include "Arduino.h"
	class NMusic{
		public:
			static int* getScale(int note, boolean major);
			static float getFrequency(int note);
			static float* getFrequency(int note[]);
			static int* getChord(int scale[], int scaleDegree, boolean up, int inverts);
			static void invertChord(int base[], boolean up);
		private:
	};
#endif