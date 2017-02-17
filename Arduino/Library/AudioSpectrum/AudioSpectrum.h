#ifndef AudioSpectrum_h
#define AudioSpectrum_h

#include "Arduino.h"

class AudioSpectrum
{
public:
	AudioSpectrum();
	void Update();

private:
	String input;
	uint8_t pixelLevel[14];
	uint8_t peakLevel[14];
	void updateLEDs();
	void initPeakLevel();
};

#endif

