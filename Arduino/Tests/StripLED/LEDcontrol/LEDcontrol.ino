#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#include <avr/pgmspace.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(280, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

const int pixelMatrice[][14] PROGMEM = 
                              //    [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]  [8]  [9] [10] [11] [12] [13]
                               { {   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13},   //[0]
                                 {  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17,  16,  15,  14},   //[1]
                                 {  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41},   //[2]
                                 {  55,  54,  53,  52,  51,  50,  49,  48,  47,  46,  45,  44,  43,  42},   //[3]
                                 {  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69},   //[4]
                                 {  83,  82,  81,  80,  79,  78,  77,  76,  75,  74,  73,  72,  71,  70},   //[5]
                                 {  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,  96,  97},   //[6]
                                 { 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100,  99,  98},   //[7]
                                 { 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125},   //[8]
                                 { 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128, 127, 126},   //[9]
                                 { 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153},   //[10]
                                 { 167, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 155, 154},   //[11]
                                 { 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181},   //[12]
                                 { 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182},   //[13]
                                 { 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209},   //[14]
                                 { 223, 222, 221, 220, 219, 218, 217, 216, 215, 214, 213, 212, 211, 210},   //[15]
                                 { 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237},   //[16]
                                 { 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240, 239, 238},   //[17]
                                 { 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265},   //[18]
                                 { 279, 278, 277, 276, 275, 274, 273, 272, 271, 270, 269, 268, 267, 266}    //[19]
                               };
//Pin Assignments
byte rightPin = 7;
byte upPin = 6;
byte leftPin = 5;
byte downPin = 4;

void setup() {
  Serial.begin(9600);
  
  //Initialize Inputs
  pinMode(rightPin, INPUT);
  pinMode(upPin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(downPin, INPUT);
  digitalWrite(rightPin, HIGH);
  digitalWrite(upPin, HIGH);
  digitalWrite(downPin, HIGH);
  digitalWrite(leftPin, HIGH);

  //Initialize LED strip
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(20);

}

void loop(){

}

void colorSpectrum(int wait){
  for(int color = 0; color < 256; color++){
    for(int j = 0; j < 14; j++){
      for(int i = 0; i < 20; i++){
        int pixelNum = pgm_read_word(&(pixelMatrice[i][j]));
        strip.setPixelColor(pixelNum, Wheel(((j*10) + color) & 255) );
        //Serial.println(pixelNum);
        //Serial.println(pixelMatrice[i][j]);
      }
    }
    delay(wait);
    strip.show();
  }
  
}

void spiral(uint8_t wait){
  uint16_t counter= 0;
  uint8_t boundLeft= 0;
  uint8_t boundBot= 0;
  
  //boundLeft < 7
  while(boundLeft < 7){

    //top
    for(int j = boundLeft; j < (14 - boundLeft); j++){
      strip.setPixelColor( pgm_read_word(&(pixelMatrice[boundBot][j])), Wheel((counter*2) & 255) );
      strip.show();
      counter++;
      delay(wait);
    }

    //right
    for(int i = boundBot + 1; i < (20 - boundBot); i++){
      strip.setPixelColor( pgm_read_word(&(pixelMatrice[i][13 - boundLeft])), Wheel((counter*2) & 255) );
      strip.show();
      counter++;
      delay(wait);
    }
    Serial.println(boundLeft);
    //bot
    for(int j = (13 - boundLeft - 1); j >= boundLeft; j--){
      strip.setPixelColor( pgm_read_word(&(pixelMatrice[19 - boundBot][j])), Wheel((counter*2) & 255) );
      strip.show();
      counter++;
      delay(wait);
    }
    boundBot++;

    //left
    for(int i = (19 - boundBot); i >= boundBot; i--){
      strip.setPixelColor( pgm_read_word(&(pixelMatrice[i][boundLeft])), Wheel((counter*2) & 255) );
      strip.show();
      counter++;
      delay(wait);
    }
    boundLeft++;
  }

}

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
