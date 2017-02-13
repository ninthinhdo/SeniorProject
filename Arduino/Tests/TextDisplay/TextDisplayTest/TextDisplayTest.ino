#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#include <avr/pgmspace.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 44

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

typedef struct Letter {
 unsigned line1 : 3;
 unsigned line2 : 3;
 unsigned line3 : 3;
 unsigned line4 : 3;
 unsigned line5 : 3;
 unsigned : 0;
};

Letter A = { 
 B010,
 B101,
 B111,
 B101,
 B101
};

Letter B = { 
 B110,
 B101,
 B110,
 B101,
 B110
};

Letter C = { 
 B111,
 B100,
 B100,
 B100,
 B111
};

Letter D = { 
 B110,
 B101,
 B101,
 B101,
 B110
};

Letter E = { 
 B111,
 B100,
 B111,
 B100,
 B111
};

Letter F = { 
 B111,
 B100,
 B111,
 B100,
 B100
};

Letter G = { 
 B111,
 B100,
 B100,
 B101,
 B111
};

Letter H = { 
 B101,
 B101,
 B111,
 B101,
 B101
};

Letter I = { 
 B111,
 B010,
 B010,
 B010,
 B111
};

Letter J = { 
 B111,
 B010,
 B010,
 B010,
 B110
};

Letter K = { 
 B101,
 B110,
 B100,
 B110,
 B101
};

Letter L = { 
 B100,
 B100,
 B100,
 B100,
 B111
};

Letter M = { 
 B101,
 B111,
 B101,
 B101,
 B101
};

Letter N = { 
 B111,
 B101,
 B101,
 B101,
 B101
};

Letter O = { 
 B111,
 B101,
 B101,
 B101,
 B111
};

Letter P = { 
 B111,
 B101,
 B111,
 B100,
 B100
};

Letter Q = { 
 B111,
 B101,
 B101,
 B111,
 B001
};

Letter R = { 
 B110,
 B101,
 B110,
 B110,
 B101
};

Letter S = { 
 B111,
 B100,
 B111,
 B001,
 B111
};

Letter T = { 
 B111,
 B010,
 B010,
 B010,
 B010
};

Letter U = { 
 B101,
 B101,
 B101,
 B101,
 B111
};

Letter V = { 
 B101,
 B101,
 B101,
 B101,
 B010
};

Letter W = { 
 B101,
 B101,
 B101,
 B111,
 B101
};

Letter X = { 
 B101,
 B101,
 B010,
 B101,
 B101
};

Letter Y = { 
 B101,
 B101,
 B010,
 B010,
 B010
};

Letter Z = { 
 B111,
 B001,
 B010,
 B100,
 B111
};

Letter s = { 
 B000,
 B000,
 B000,
 B000,
 B000
};

Letter *Alphabet[] = { &A, &B, &C, &D, &E, &F, &G, &H, &I, &J, &K, &L, &M, &N, &O, &P, &Q, &R, &S, &T, &U, &V, &W, &X, &Y, &Z};

//Colors
const uint32_t red = strip.Color(255, 0, 0);
const uint32_t green = strip.Color(0, 255, 0);
const uint32_t blue = strip.Color(0, 0, 255);
const uint32_t yellow = strip.Color(255, 255, 0);
const uint32_t cyan = strip.Color(0, 255, 255);
const uint32_t magenta = strip.Color(255, 0, 255);
const uint32_t colorPick[] = { red, green, blue, green, cyan, magenta};

void setup() {
  Serial.begin(9600);
  
  //Initialize LED strip
  strip.begin();
  strip.show();
  strip.setBrightness(50);

  //Serial.println(A[0][0]);
  //Serial.println(Letters[0][4]);
}

void loop(){
  Serial.println(Alphabet[0]->line3);
  
  char myWord[] = "HELLO WORLD";
  byte wordLength = sizeof(myWord);
  printWord(myWord, wordLength, 6, 14, magenta);
  
  /*
  char newWord[] = "JOHNNY";
  wordLength = sizeof(newWord);
  printWord(newWord, wordLength, 6, 14);
  */
}

void printWord(char charArray[], byte len, int rowPos, int colPos, uint32_t textColor){
  bool scrolling = false;
  int initialRow = rowPos;
  int initialCol = colPos;
  if((colPos + ((len - 1) * 4) - 1) > 13) scrolling = true;
  
  //Enable scrolling
  if(scrolling){
    for(int scrollIndex = 0; scrollIndex < (colPos + ((len + 1) * 4)); scrollIndex++){
      colPos = initialCol - scrollIndex;
      
      clearStrip(initialRow);

      //Print each text with an empty column for space
      for(int i = 0; i < len - 1; i++){
        byte index = (byte)charArray[i] - 'A';

        if(charArray[i] == ' '){
          colPos +=2;
        }else{
          
          for(int c = 0; c < 3; c++){
            if(((colPos + (2-c)) < 14) && ((colPos + (2-c)) >= 0)){
              if(bitRead(Alphabet[index]->line1,c)) strip.setPixelColor(pgm_read_word(&(pixelMatrice[rowPos][colPos + (2-c)])), textColor);
              if(bitRead(Alphabet[index]->line2,c)) strip.setPixelColor(pgm_read_word(&(pixelMatrice[rowPos + 1][colPos + (2-c)])), textColor);
              if(bitRead(Alphabet[index]->line3,c)) strip.setPixelColor(pgm_read_word(&(pixelMatrice[rowPos + 2][colPos + (2-c)])), textColor);
              if(bitRead(Alphabet[index]->line4,c)) strip.setPixelColor(pgm_read_word(&(pixelMatrice[rowPos + 3][colPos + (2-c)])), textColor);
              if(bitRead(Alphabet[index]->line5,c)) strip.setPixelColor(pgm_read_word(&(pixelMatrice[rowPos + 4][colPos + (2-c)])), textColor);
            }
          }
          colPos += 4;
        }
      }
      strip.show();
      delay(150);
      
      
    }

  //Print static text
  }else{
    for(int i = 0; i < len - 1; i++){
      byte index = (byte)charArray[i] - 'A';
      
      if(charArray[i] == ' '){
          colPos +=2;
      }else{
        for(int c = 0; c < 3; c++){
          if(((colPos + (2-c)) < 14) && ((colPos + (2-c)) >= 0)){
            if(bitRead(Alphabet[index]->line1,c)) strip.setPixelColor(pgm_read_word(&(pixelMatrice[rowPos][colPos + (2-c)])), textColor);
            if(bitRead(Alphabet[index]->line2,c)) strip.setPixelColor(pgm_read_word(&(pixelMatrice[rowPos + 1][colPos + (2-c)])), textColor);
            if(bitRead(Alphabet[index]->line3,c)) strip.setPixelColor(pgm_read_word(&(pixelMatrice[rowPos + 2][colPos + (2-c)])), textColor);
            if(bitRead(Alphabet[index]->line4,c)) strip.setPixelColor(pgm_read_word(&(pixelMatrice[rowPos + 3][colPos + (2-c)])), textColor);
            if(bitRead(Alphabet[index]->line5,c)) strip.setPixelColor(pgm_read_word(&(pixelMatrice[rowPos + 4][colPos + (2-c)])), textColor);
          }
        }
        colPos += 4;
      }
      strip.show();
    }
  }
}

void clearStrip(int initialRow){
  for(int c = 0; c < 14; c++){
    for(int r = 0; r < 5; r++){
      strip.setPixelColor(pgm_read_word(&(pixelMatrice[initialRow + r][c])), 0);
    }
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



/*
byte A[][3] =
                            { { 0, 1, 0},
                              { 1, 0, 1},
                              { 1, 1, 1},
                              { 1, 0, 1},
                              { 1, 0, 1} };

byte B[][3] =
                            { { 1, 1, 0},
                              { 1, 0, 1},
                              { 1, 1, 0},
                              { 1, 0, 1},
                              { 1, 1, 0} };

byte* Letters[] = {&A[0][0], &B[0][0]};
*/
