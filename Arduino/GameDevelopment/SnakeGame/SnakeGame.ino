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

//0 is off, 1 is on for LEDs
byte logicMatrice[20][14];

//Sound Pins
const byte backgroundPin = 22;
const byte countdownPin = 24;
const byte crashPin = 26;
const byte resetSoundPin = 30;

//Definations
#define MAX_LENGTH 100

//Variables
byte direction; //0 is right, 1 is up, 2 is left, 3 is down
byte row, col;
bool right, up, left, down;
bool crash;
uint32_t snakeColor;
byte tail, head;
byte posRow[MAX_LENGTH];
byte posCol[MAX_LENGTH];
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
  strip.setBrightness(32);

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
  strip.setPixelColor(PixelMatrice[posRow[tail]][posCol[tail]], 0);
  logicMatrice[posRow[tail]][posCol[tail]] = 0;
  tail++;
  if(tail == 100) tail = 0;

  //Assign Head
  head++;
  if(head == 100) head = 0;
  posRow[head] = row;
  posCol[head] = col;
  strip.setPixelColor(PixelMatrice[row][col], snakeColor);
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
    } else if(inputCommand.equals("BReset")){
      pauseGame();
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
    if (col == MAX_COL){
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
    if (row == MAX_ROW){
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
      strip.setPixelColor(PixelMatrice[row][col], white);
      strip.show();
      delay(wait);
      strip.setPixelColor(PixelMatrice[row][col], snakeColor);
      strip.show();
      delay(wait);
    }
}

void blinkTail(uint16_t wait){
    for(int i = 0; i < 4 ; i++){
      strip.setPixelColor(PixelMatrice[posRow[tail - 1]][posCol[tail-1]], 0);
      strip.show();
      delay(wait);
      strip.setPixelColor(PixelMatrice[posRow[tail - 1]][posCol[tail-1]], snakeColor);
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
  for(int i = 0; i < MAX_LENGTH; i++){
    posRow[i] = 0;
    posCol[i] = 0;
  }

  //Setup Random Generator
  randomSeed(analogRead(0));
  delay(20);
  int varRandom;
  for(int i = 0; i < (analogRead(0) % 10); i++) varRandom = random(0, sizeof(ColorPick) / 4);

  //Initialize Snake
  posRow[0] = row;
  posCol[0] = col;
  snakeColor = ColorPick[varRandom];
  strip.setPixelColor(PixelMatrice[row][col], snakeColor);
  logicMatrice[row][col] = 1;
  strip.show();

  foodColor = ColorPick[random(0, sizeof(ColorPick) / 4)];
  while(foodColor == snakeColor) foodColor = ColorPick[random(0, sizeof(ColorPick) / 4)];
}

void genFood(){
  foodRow = random(0,MAX_ROW);
  foodCol = random(0,MAX_COL);

  foodColor = ColorPick[random(0, sizeof(ColorPick) / 4)];
  while(foodColor == snakeColor) foodColor = ColorPick[random(0, sizeof(ColorPick) / 4)];

  while(logicMatrice[foodRow][foodCol]){
    foodRow = random(0,MAX_ROW);
    foodCol = random(0,MAX_COL);
  }

  strip.setPixelColor(PixelMatrice[foodRow][foodCol], foodColor);
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
      if(bitRead(Numbers[index]->line1,c)) strip.setPixelColor(PixelMatrice[rowPos][colPos + (2-c)], textColor);
      if(bitRead(Numbers[index]->line2,c)) strip.setPixelColor(PixelMatrice[rowPos + 1][colPos + (2-c)], textColor);
      if(bitRead(Numbers[index]->line3,c)) strip.setPixelColor(PixelMatrice[rowPos + 2][colPos + (2-c)], textColor);
      if(bitRead(Numbers[index]->line4,c)) strip.setPixelColor(PixelMatrice[rowPos + 3][colPos + (2-c)], textColor);
      if(bitRead(Numbers[index]->line5,c)) strip.setPixelColor(PixelMatrice[rowPos + 4][colPos + (2-c)], textColor);
    }
  }
  strip.show();
}

void clearStrip(int initialRow){
  for(int c = 0; c < 14; c++){
    for(int r = 0; r < 5; r++){
      strip.setPixelColor(PixelMatrice[initialRow + r][c], 0);
    }
  }
}
