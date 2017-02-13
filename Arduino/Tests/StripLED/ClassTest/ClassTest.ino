#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#include <avr/pgmspace.h>
#include <TronBike.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 13

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
//0 is off, 1 is on for LEDs
byte logicMatrice[20][14];

//Colors
const uint32_t red = strip.Color(255, 0, 0);
const uint32_t green = strip.Color(0, 255, 0);
const uint32_t blue = strip.Color(0, 0, 255);
const uint32_t yellow = strip.Color(255, 255, 0);
const uint32_t cyan = strip.Color(0, 255, 255);
const uint32_t magenta = strip.Color(255, 0, 255);
const uint32_t colorPick[] = { red, green, blue, green, cyan, magenta};

//TronBike param (int rightPin, int upPin, int leftPin, int downPin, int bikeRow, int bikeCol, int initialDirection, uint32_t c);
/* Bike Direction
 * 0 --> right
 * 1 --> up
 * 2 --> left
 * 3 --> down
 */
TronBike bike1(46, 48, 50, 52, 7, 12, 2, green);
TronBike bike2(47, 49, 51, 53, 7, 1, 0, red);

int pausePin = 44;

void setup() {
  Serial.begin(9600);

  //Initialize pins
  pinMode(pausePin, INPUT);
  digitalWrite(pausePin, HIGH);
  
  //Initialize logicMatrice to zeros;
  clearMatrice();
  
  //Initialize LED strip
  strip.begin();
  strip.setBrightness(30);

  //Tron Bikes
  initializeBike(bike1);
  initializeBike(bike2);
}

void loop(){

  byte pauseBtn = digitalRead(pausePin);
  if(pauseBtn == LOW){
    pauseGame();
  }
  
  bike1.inputDirection();
  bike1.updatePosition();
  strip.setPixelColor(pgm_read_word(&(pixelMatrice[bike1.row][bike1.col])), bike1.color);
  strip.show();
  
  bike2.inputDirection();
  bike2.updatePosition();
  strip.setPixelColor(pgm_read_word(&(pixelMatrice[bike2.row][bike2.col])), bike2.color);
  strip.show();
  
  if(logicMatrice[bike1.row][bike1.col] == 1){
    clearMatrice();
    strip.clear();
    resetGame();
  }else{
    logicMatrice[bike1.row][bike1.col] = 1;
  }
  
  if(logicMatrice[bike2.row][bike2.col] == 1){
    clearMatrice();
    strip.clear();
    resetGame();
  }else{
    logicMatrice[bike2.row][bike2.col] = 1;
  }
  
  delay(200);
}

void pauseGame(){
  delay(3000);
  byte tempPause = digitalRead(pausePin);
  while(tempPause == HIGH) tempPause = digitalRead(pausePin);
  delay(200);
}

void resetGame(){
  bike1.row = 7;
  bike1.col = 12;
  bike1.direction = 2;
  strip.setPixelColor(pgm_read_word(&(pixelMatrice[bike1.row][bike1.col])), bike1.color);
  logicMatrice[bike1.row][bike1.col] = 1;
  
  bike2.row = 7;
  bike2.col = 1;
  bike2.direction = 0;
  strip.setPixelColor(pgm_read_word(&(pixelMatrice[bike2.row][bike2.col])), bike2.color);
  logicMatrice[bike2.row][bike2.col] = 1;
  strip.show();
  delay(1000);
}

void initializeBike(TronBike &bike){
  //Setup Random Generator
  randomSeed(analogRead(0));
  delay(20);
  int varRandom;
  for(int i = 0; i < (analogRead(0) % 10); i++) varRandom = random(0,7);

  //Initialize bike
  bike.color = colorPick[varRandom];
  strip.setPixelColor(pgm_read_word(&(pixelMatrice[bike.row][bike.col])), bike.color);
  logicMatrice[bike.row][bike.col] = 1;
  strip.show();
  delay(900);
}

void clearMatrice(){
  for(int i = 0; i < 20; i++){
    for(int j = 0; j < 14; j++) logicMatrice[i][j] = 0;
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
