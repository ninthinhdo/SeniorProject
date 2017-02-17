#include "Arduino.h"
#include "AudioSpectrum.h"

#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
#include "avr/power.h"
#endif
#include "avr/pgmspace.h"

#define PIN 44
Adafruit_NeoPixel spectrum_strip = Adafruit_NeoPixel(280, PIN, NEO_GRB + NEO_KHZ800);

#include "PixelResource.h"

AudioSpectrum::AudioSpectrum()
{
	spectrum_strip.begin();
	spectrum_strip.setBrightness(32);
	spectrum_strip.clear();

	initPeakLevel();

	Serial2.print("FFT.");
}


void AudioSpectrum::Update()
{
	for (int i = 0; i < 20; i++){

		if (Serial2.available() > 0){
			Serial2.readBytesUntil('X', pixelLevel, 14);
			while (Serial2.available() > 14) Serial2.readBytesUntil('X', pixelLevel, 14);
			updateLEDs();
		}
	}
}


void AudioSpectrum::updateLEDs()
{
	for (int col = 0; col <= MAX_COL; col++){
		// Skip if input level is lower than peakLevel && filter out extraneous values
		if ((pixelLevel[col] > peakLevel[col]) && !(pixelLevel[col] > MAX_ROW)){
			for (int row = peakLevel[col]; row < pixelLevel[col]; row++){
				spectrum_strip.setPixelColor(PixelMatrice[MAX_ROW - row][col], ColorPick[col % 10]);
			}
			// Assign new peak
			peakLevel[col] = pixelLevel[col];
		}
		else{
			// Lower peak
			spectrum_strip.setPixelColor(PixelMatrice[MAX_ROW - peakLevel[col]][col], 0);
			if (peakLevel[col] > 0) peakLevel[col]--;
		}

		/*if (pixelLevel[col] > 19){
			Serial.print("Col ");
			Serial.print(col);
			Serial.print(" : ");
			Serial.println(pixelLevel[col]);
		}*/
	}
	spectrum_strip.show();
}

void AudioSpectrum::initPeakLevel()
{
	for (int i = 0; i <= MAX_COL; i++){
		peakLevel[i] = 0;
	}
}