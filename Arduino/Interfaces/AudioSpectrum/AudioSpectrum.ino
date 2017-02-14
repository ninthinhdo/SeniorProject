#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include <avr/pgmspace.h>

#define PIN 44

Adafruit_NeoPixel strip = Adafruit_NeoPixel(280, PIN, NEO_GRB + NEO_KHZ800);
#include <PixelStruct.h>
#include <PixelResource.h>

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

// My Variables
String input;
uint8_t pixelLevel[14];
uint8_t peakLevel[14];

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  
  // Initialize LED strip
  strip.begin();
  strip.setBrightness(32);

  initPeakLevel();

  Serial2.print("FFT.");
}

void loop()
{
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    input = Serial.readStringUntil('.');
    Serial2.print(input + '.');
  }

  if(Serial2.available() > 0){
    Serial2.readBytesUntil('X', pixelLevel, 14);
    while(Serial2.available() > 14) Serial2.readBytesUntil('X', pixelLevel, 14);
    updateLEDs();
  }

}

void updateLEDs()
{
  for(int col = 0; col <= MAX_COL; col++){
    // Skip if input level is lower than peakLevel && filter out extraneous values
    if((pixelLevel[col] > peakLevel[col]) && !(pixelLevel[col] > MAX_ROW)){
      for(int row = peakLevel[col]; row < pixelLevel[col]; row++){
         strip.setPixelColor(PixelMatrice[MAX_ROW - row][col], ColorPick[col % 10]);
      }
      // Assign new peak
      peakLevel[col] = pixelLevel[col];
    }
    else{
      // Lower peak
      strip.setPixelColor(PixelMatrice[MAX_ROW - peakLevel[col]][col], 0);
      if(peakLevel[col] > 0) peakLevel[col]--;
    }
    
    if(pixelLevel[col] > 19){
      Serial.print("Col ");
      Serial.print(col);
      Serial.print(" : ");
      Serial.println(pixelLevel[col]);
    }
  }
  strip.show();
}

void initPeakLevel()
{
  for(int i = 0; i <= MAX_COL; i++){
    peakLevel[i] = 0;
  }
}


