#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include <avr/pgmspace.h>

#define PIN 44

Adafruit_NeoPixel strip = Adafruit_NeoPixel(280, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

const int pixelMatrice[][14] =
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

struct Number {
  unsigned line1 : 3;
  unsigned line2 : 3;
  unsigned line3 : 3;
  unsigned line4 : 3;
  unsigned line5 : 3;
  unsigned : 0;
};
typedef struct Number Number;

Number zero = {
    B111,
    B101,
    B101,
    B101,
    B111
  };

  Number one = {
    B010,
    B110,
    B010,
    B010,
    B111
  };

  Number two = {
    B111,
    B001,
    B111,
    B100,
    B111
  };

  Number three = {
    B111,
    B001,
    B111,
    B001,
    B111
  };

  Number four = {
    B101,
    B101,
    B111,
    B001,
    B001
  };

  Number five = {
    B111,
    B100,
    B111,
    B001,
    B111
  };

  Number six = {
    B111,
    B100,
    B111,
    B101,
    B111
  };

  Number seven = {
    B111,
    B001,
    B001,
    B001,
    B001
  };

  Number eight = {
    B111,
    B101,
    B111,
    B101,
    B111
  };

  Number nine = {
    B111,
    B101,
    B111,
    B001,
    B001
  };

  Number dash = {
    B000,
    B000,
    B111,
    B000,
    B000
  };

  Number *Numbers[] = { &zero, &one, &two, &three, &four, &five, &six, &seven, &eight, &nine, &dash };

//Colors
const uint32_t red = strip.Color(255, 0, 0);
const uint32_t green = strip.Color(0, 255, 0);
const uint32_t blue = strip.Color(0, 0, 255);
const uint32_t yellow = strip.Color(255, 255, 0);
const uint32_t cyan = strip.Color(0, 255, 255);
const uint32_t magenta = strip.Color(255, 0, 255);
const uint32_t chocolate = strip.Color(210, 105, 30);
const uint32_t orange = strip.Color(255, 165, 0);
const uint32_t seaGreen = strip.Color(60, 179, 113);
const uint32_t hotPink = strip.Color(255, 20, 147);
const uint32_t white = strip.Color(255, 255, 255);
const uint32_t colorPick[] = { red, green, blue, green, cyan, magenta, chocolate, orange, seaGreen, hotPink};

//Sound Pins
const byte backgroundPin = 22;
const byte countdownPin = 24;
const byte crashPin = 26;
const byte resetSoundPin = 30;

//Constants
const byte maxRow = 19;
const byte maxCol = 13;
const byte maxLength = 100;
//Variables
byte direction; //0 is right, 1 is up, 2 is left, 3 is down
byte row, col;
bool right, up, left, down;
bool crash;
uint32_t snakeColor;
byte tail, head;
byte posRow[maxLength];
byte posCol[maxLength];
byte foodRow, foodCol;
uint32_t foodColor;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  //Initialize pins
  pinMode(backgroundPin, OUTPUT);
  pinMode(countdownPin, OUTPUT);
  pinMode(crashPin, OUTPUT);
  pinMode(resetSoundPin, OUTPUT);

  digitalWrite(backgroundPin, HIGH);
  digitalWrite(countdownPin, HIGH);
  digitalWrite(crashPin, HIGH);
  digitalWrite(resetSoundPin, LOW);

  //Initialize logicMatrice to zeros;
  clearLogicMatrice();

  //Initialize LED strip
  strip.begin();
  strip.setBrightness(100);

  //Initialize Snake
  initializeSnake();

  delay(100);
  digitalWrite(resetSoundPin, HIGH);
  delay(1500);

  //Start Countdown
  countDown();

  //Generate Food
  genFood();
}

void loop() {

  /*
  String pauseBtn = Serial1.readStringUntil('.');
  if(pauseBtn.equals("BReset")){
    pauseGame();
  }
  */

  //200ms delay
  waitForInput(100);

  updateFrame();

}

void waitForInput(int wait){
  for(int i = 0; i < wait; i++){
    inputDirection();
    delay(1);
  }
}

void updateFrame(){

  updateDirection();
  updatePosition();

  //Erase Tail
  strip.setPixelColor(pixelMatrice[posRow[tail]][posCol[tail]], 0);
  logicMatrice[posRow[tail]][posCol[tail]] = 0;
  tail++;
  if(tail == 100) tail = 0;

  //Assign Head
  head++;
  if(head == 100) head = 0;
  posRow[head] = row;
  posCol[head] = col;
  strip.setPixelColor(pixelMatrice[row][col], snakeColor);
  strip.show();

  //Food Eaten
  if((row == foodRow) && (col == foodCol)){
    blinkTail(100);
    tail--;
    //Generate new food
    genFood();
  }

  if(logicMatrice[row][col] == 1){
    crash = true;
  }else{
    logicMatrice[row][col] = 1;
  }

  if(crash){
    blinkHead(190);
    strip.clear();
    resetGame();
  }
}

void inputDirection(){
  if(Serial1.available() > 0){
    //Read INPUTS
    String inputCommand = Serial1.readStringUntil('.');

    if (inputCommand.equals("BUp")){
      right = false;
      up = true;
      left = false;
      down = false;
    } else if (inputCommand.equals("BRight")){
      right = true;
      up = false;
      left = false;
      down = false;
    } else if (inputCommand.equals("BDown")){
      right = false;
      up = false;
      left = false;
      down = true;
    } else if (inputCommand.equals("BLeft")){
      right = false;
      up = false;
      left = true;
      down = false;
    }

  }
}

void updateDirection(){
  //Change direction
  switch (direction){
  case 0:
    if (down == true){
      direction = 3;
    }
    else if (up == true){
      direction = 1;
    }
    break;
  case 1:
    if (left == true){
      direction = 2;
    }
    else if (right == true){
      direction = 0;
    }
    break;
  case 2:
    if (down == true){
      direction = 3;
    }
    else if (up == true){
      direction = 1;
    }
    break;
  case 3:
    if (left == true){
      direction = 2;
    }
    else if (right == true){
      direction = 0;
    }
    break;
  default:
    break;
  }

  right = false;
  up = false;
  left = false;
  down = false;
}

void updatePosition(){
  //Update new position
  switch (direction){
  case 0:
    if (col == maxCol){
      crash = true;
    }
    else{
      col++;
    }
    break;

  case 1:
    if (row == 0){
      crash = true;
    }
    else{
      row--;
    }
    break;

  case 2:
    if (col == 0){
      crash = true;
    }
    else{
      col--;
    }
    break;

  case 3:
    if (row == maxRow){
      crash = true;
    }
    else{
      row++;
    }
    break;

  default:
    break;
  }
}


void blinkHead(uint16_t wait){
  digitalWrite(crashPin, LOW);
  delay(10);
  digitalWrite(crashPin, HIGH);

  for(int i = 0; i < 4 ; i++){
      strip.setPixelColor(pixelMatrice[row][col], white);
      strip.show();
      delay(wait);
      strip.setPixelColor(pixelMatrice[row][col], snakeColor);
      strip.show();
      delay(wait);
    }
}

void blinkTail(uint16_t wait){
    for(int i = 0; i < 4 ; i++){
      strip.setPixelColor(pixelMatrice[posRow[tail - 1]][posCol[tail-1]], 0);
      strip.show();
      delay(wait);
      strip.setPixelColor(pixelMatrice[posRow[tail - 1]][posCol[tail-1]], snakeColor);
      strip.show();
      delay(wait);
    }

    logicMatrice[posRow[tail - 1]][posCol[tail - 1]] = 1;
}

void initializeSnake(){
  right = false;
  up = false;
  left = false;
  down = false;

  direction = 0; //goes right
  crash = false;

  row = 10;
  col = 7;

  tail = 0;
  head = 0;

  //Erase snake positions
  for(int i = 0; i < maxLength; i++){
    posRow[i] = 0;
    posCol[i] = 0;
  }

  //Setup Random Generator
  randomSeed(analogRead(0));
  delay(20);
  int varRandom;
  for(int i = 0; i < (analogRead(0) % 10); i++) varRandom = random(0, sizeof(colorPick) / 4);

  //Initialize Snake
  posRow[0] = row;
  posCol[0] = col;
  snakeColor = colorPick[varRandom];
  strip.setPixelColor(pixelMatrice[row][col], snakeColor);
  logicMatrice[row][col] = 1;
  strip.show();

  foodColor = colorPick[random(0, sizeof(colorPick) / 4)];
  while(foodColor == snakeColor) foodColor = colorPick[random(0, sizeof(colorPick) / 4)];
}

void genFood(){
  foodRow = random(0,maxRow);
  foodCol = random(0,maxCol);

  foodColor = colorPick[random(0, sizeof(colorPick) / 4)];
  while(foodColor == snakeColor) foodColor = colorPick[random(0, sizeof(colorPick) / 4)];

  while(logicMatrice[foodRow][foodCol]){
    foodRow = random(0,maxRow);
    foodCol = random(0,maxCol);
  }

  strip.setPixelColor(pixelMatrice[foodRow][foodCol], foodColor);
}

void pauseGame(){
  delay(3000);
  String tempPause = Serial1.readStringUntil('.');
  while(!tempPause.equals("BReset")) tempPause = Serial1.readStringUntil('.');
  delay(200);
}

void resetGame(){
  clearLogicMatrice();
  initializeSnake();
  countDown();
  genFood();
}

void clearLogicMatrice(){
  for(int i = 0; i < 20; i++){
    for(int j = 0; j < 14; j++) logicMatrice[i][j] = 0;
  }
}

void countDown(){
  digitalWrite(countdownPin, LOW);
  delay(10);
  digitalWrite(countdownPin, HIGH);
  for(int i = 3; i >= 0; i--){
    printNum(i, 1, 6, cyan);
    delay(1000);
    clearStrip(1);
  }
  delay(100);
  digitalWrite(backgroundPin, LOW);
  delay(10);
  digitalWrite(backgroundPin, HIGH);
}

void printNum(byte index, int rowPos, int colPos, uint32_t textColor){
  for(int c = 0; c < 3; c++){
    if(((colPos + (2-c)) < 14) && ((colPos + (2-c)) >= 0)){
      if(bitRead(Numbers[index]->line1,c)) strip.setPixelColor(pixelMatrice[rowPos][colPos + (2-c)], textColor);
      if(bitRead(Numbers[index]->line2,c)) strip.setPixelColor(pixelMatrice[rowPos + 1][colPos + (2-c)], textColor);
      if(bitRead(Numbers[index]->line3,c)) strip.setPixelColor(pixelMatrice[rowPos + 2][colPos + (2-c)], textColor);
      if(bitRead(Numbers[index]->line4,c)) strip.setPixelColor(pixelMatrice[rowPos + 3][colPos + (2-c)], textColor);
      if(bitRead(Numbers[index]->line5,c)) strip.setPixelColor(pixelMatrice[rowPos + 4][colPos + (2-c)], textColor);
    }
  }
  strip.show();
}

void clearStrip(int initialRow){
  for(int c = 0; c < 14; c++){
    for(int r = 0; r < 5; r++){
      strip.setPixelColor(pixelMatrice[initialRow + r][c], 0);
    }
  }
}
