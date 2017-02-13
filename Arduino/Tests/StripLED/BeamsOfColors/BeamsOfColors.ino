#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(280, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(255);
}

void loop() {

  //colorSpectrumFade(30);
  //colorSpectrumFlow(30);
  //rainbow(10);
  
  int beamSpeed = 10;
  colorBeam(255, 0, 0, 12, beamSpeed);
  colorBeam(0, 255, 0, 12, beamSpeed);
  colorBeam(0, 0, 255, 12, beamSpeed);
}

void colorSpectrumFlow(uint8_t wait){
  uint8_t i, j;
  j = 0;
  while(true){
    for(i = strip.numPixels() - 1; i > 0 ; i--){
      strip.setPixelColor(i, strip.getPixelColor(i-1));
    }
    strip.setPixelColor(0, Wheel(j));
    strip.show();
    delay(wait);
    
    if(j == 255){
      j = 0;
    }else{
      j++;
    }
  }
  
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void colorSpectrumFade(uint8_t wait){
  uint8_t i,j;
  for(j = 0; j < 256; j++){
    for(i = 0; i < strip.numPixels(); i++){
      strip.setPixelColor(i, Wheel(j));
    }
    delay(wait);
    strip.show();
  }
  
}

void colorBeam(uint8_t R, uint8_t G, uint8_t B, uint8_t len, uint8_t wait){
  for(uint16_t i = 0; i < (strip.numPixels() + len + 1); i++){
    for(uint8_t j = 0; j < len; j++){
      if(((i-j) >= 0) && ((i-j) < (strip.numPixels() + len))){
        if(R > 0){
          strip.setPixelColor(i-j, strip.Color(R - (j*20),G,B));
        }else if(G > 0){
          strip.setPixelColor(i-j, strip.Color(R,G - (j*20),B));
        }else if(B > 0){
          strip.setPixelColor(i-j, strip.Color(R,G,B - (j*20)));
        }
        
      }
      if((i - len - 1) >= 0){
        strip.setPixelColor(i-len - 1, 0);
      }
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
