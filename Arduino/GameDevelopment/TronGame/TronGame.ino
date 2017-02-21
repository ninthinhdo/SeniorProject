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
#include <TronBike.h>

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

//0 is off, 1 is on for LEDs
byte logicMatrice[20][14];

//TronBike param (int rightPin, int upPin, int leftPin, int downPin, int bikeRow, int bikeCol, int initialDirection, uint32_t c);
/* Bike Direction
 * 0 --> right
 * 1 --> up
 * 2 --> left
 * 3 --> down
 */
 
TronBike bike1("BRight", "BUp", "BLeft", "BDown", 7, 12, 2, red);
TronBike bike2("JRight", "JUp", "JLeft", "JDown", 7, 1, 0, green);

int score1;
int score2;
char scoreDisplay[] = "0-0";
byte setWinScore = 5;

String command;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);  // To Nano, Game Controller
  Serial2.begin(9600);  // To Teensy, Audio
  
  //Initialize logicMatrice to zeros;
  clearLogicMatrice();
  
  //Initialize LED strip
  strip.begin();
  strip.setBrightness(32);
  strip.clear();

  // Play Tetris Theme
  Serial2.print("STOP.GAME.ARCADE2.");

  // Initialize game settings
  score1 = 0;
  score2 = 0;
  
  // Tron Bikes
  initializeBike(bike1);
  initializeBike(bike2);
  while(bike2.color == bike1.color) initializeBike(bike2);
  
  // Start Countdown
  countDown();
}

void loop()
{
  //200ms delay
  waitForInput(200);
  updateFrame();

}

void waitForInput(int wait)
{
  for(int i = 0; i < wait; i++){
    if(Serial1.available() > 0){
      command = Serial1.readStringUntil('.');
      bike1.inputDirection(command);
      bike2.inputDirection(command);
    }
    delay(1);
  }
}

void updateFrame()
{
  bool crash1 = false;
  bool crash2 = false;
  
  bike1.updateDirection();
  bike2.updateDirection();

  bike1.updatePosition();
  bike2.updatePosition();
  
  strip.setPixelColor(PixelMatrice[bike1.row][bike1.col], bike1.color);
  strip.setPixelColor(PixelMatrice[bike2.row][bike2.col], bike2.color);
  
  strip.show();
  
  if(logicMatrice[bike1.row][bike1.col] == 1){
    crash1 = true;
  }else{
    logicMatrice[bike1.row][bike1.col] = 1;
  }
  
  if(logicMatrice[bike2.row][bike2.col] == 1){
    crash2 = true;
  }else{
    logicMatrice[bike2.row][bike2.col] = 1;
  }

  if(crash1 || crash2){
    if(crash1 && crash2) blinkBike(bike1, true, 190);
    else if(crash1){
      score2++;
      blinkBike(bike1, false, 190);
    }else if(crash2){
      score1++;
      blinkBike(bike2, false, 190);
    }
    strip.clear();
    printScore(3000);
    
    resetGame();
  }
}

void blinkBike(TronBike &bike, bool both, uint16_t wait)
{
  Serial2.print("DEATH2.");
  
  if(both){
    for(int i = 0; i < 4 ; i++){
      strip.setPixelColor(PixelMatrice[bike1.row][bike1.col], white);
      strip.setPixelColor(PixelMatrice[bike2.row][bike2.col], white);
      strip.show();
      delay(wait);
      strip.setPixelColor(PixelMatrice[bike1.row][bike1.col], bike1.color);
      strip.setPixelColor(PixelMatrice[bike2.row][bike2.col], bike2.color);
      strip.show();
      delay(wait);
    }
  }else{
    for(int i = 0; i < 4 ; i++){
      strip.setPixelColor(PixelMatrice[bike.row][bike.col], white);
      strip.show();
      delay(wait);
      strip.setPixelColor(PixelMatrice[bike.row][bike.col], bike.color);
      strip.show();
      delay(wait);
    }
  }
}

void initializeBike(TronBike &bike)
{
  //Setup Random Generator
  randomSeed(analogRead(0));
  delay(20);
  int varRandom;
  for(int i = 0; i < (analogRead(0) % 10); i++) varRandom = random(0, sizeof(ColorPick) / 4);

  //Initialize bike
  bike.color = ColorPick[varRandom];
  strip.setPixelColor(PixelMatrice[bike.row][bike.col], bike.color);
  logicMatrice[bike.row][bike.col] = 1;
  strip.show();
}

void printScore(int wait)
{
  scoreDisplay[0] = (char)score2 + '0';
  scoreDisplay[2] = (char)score1 + '0';
  
  byte wordLength = sizeof(scoreDisplay);
  printWord(scoreDisplay, wordLength, 13, 2);
  
  delay(wait);

  if(score1 == setWinScore) winnerCircle(bike1.color, 100);
  else if(score2 == setWinScore) winnerCircle(bike2.color, 100);
    
  strip.clear();
}

void printWord(char charArray[], byte len, int rowPos, int colPos){
  bool scrolling = false;
  int initialRow = rowPos;
  int initialCol = colPos;
  uint32_t textColor;
  if((colPos + ((len - 1) * 4) - 1) > 13) scrolling = true;
  
  //Enable scrolling
  if(scrolling){
    for(int scrollIndex = 0; scrollIndex < (colPos + ((len + 1) * 4)); scrollIndex++){
      colPos = initialCol - scrollIndex;
      
      clearStrip(initialRow);

      //Print each text with an empty column for space
      for(int i = 0; i < len - 1; i++){
        byte index = (byte)charArray[i] - '0';

        if(charArray[i] == '-'){
        index = 10;
        }
      
        for(int c = 0; c < 3; c++){
          if(((colPos + (2-c)) < 14) && ((colPos + (2-c)) >= 0)){
            if(bitRead(Numbers[index]->line1,c)) strip.setPixelColor(PixelMatrice[rowPos][colPos + (2-c)], textColor);
            if(bitRead(Numbers[index]->line2,c)) strip.setPixelColor(PixelMatrice[rowPos + 1][colPos + (2-c)], textColor);
            if(bitRead(Numbers[index]->line3,c)) strip.setPixelColor(PixelMatrice[rowPos + 2][colPos + (2-c)], textColor);
            if(bitRead(Numbers[index]->line4,c)) strip.setPixelColor(PixelMatrice[rowPos + 3][colPos + (2-c)], textColor);
            if(bitRead(Numbers[index]->line5,c)) strip.setPixelColor(PixelMatrice[rowPos + 4][colPos + (2-c)], textColor);
          }
        }
        colPos += 4;
      }  
      strip.show();
      delay(150);
    }
    
  //Print static text
  }else{
    for(int i = 0; i < len - 1; i++){
      byte index = (byte)charArray[i] - '0';

      if(i == 0){
        textColor = bike2.color;
      }else if(i == 2){
        textColor = bike1.color;
      }else if(charArray[i] == '-'){
        index = 10;
        textColor = yellow;
      }
      
      for(int c = 0; c < 3; c++){
        if(((colPos + (2-c)) < 14) && ((colPos + (2-c)) >= 0)){
          if(bitRead(Numbers[index]->line1,c)) strip.setPixelColor(PixelMatrice[rowPos][colPos + (2-c)], textColor);
          if(bitRead(Numbers[index]->line2,c)) strip.setPixelColor(PixelMatrice[rowPos + 1][colPos + (2-c)], textColor);
          if(bitRead(Numbers[index]->line3,c)) strip.setPixelColor(PixelMatrice[rowPos + 2][colPos + (2-c)], textColor);
          if(bitRead(Numbers[index]->line4,c)) strip.setPixelColor(PixelMatrice[rowPos + 3][colPos + (2-c)], textColor);
          if(bitRead(Numbers[index]->line5,c)) strip.setPixelColor(PixelMatrice[rowPos + 4][colPos + (2-c)], textColor);
        }
      }
      colPos += 4;
    }
    strip.show();
  }
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

void pauseGame(){
  delay(3000);
  String tempPause = Serial1.readStringUntil('.');
  while (!tempPause.equals("BReset")) tempPause = Serial1.readStringUntil('.');
  delay(200);
}

void resetGame(){
  clearLogicMatrice();
  
  bike1.row = 7;
  bike1.col = 12;
  bike1.direction = 2;
  strip.setPixelColor(PixelMatrice[bike1.row][bike1.col], bike1.color);
  logicMatrice[bike1.row][bike1.col] = 1;
  
  bike2.row = 7;
  bike2.col = 1;
  bike2.direction = 0;
  strip.setPixelColor(PixelMatrice[bike2.row][bike2.col], bike2.color);
  logicMatrice[bike2.row][bike2.col] = 1;
  strip.show();
  
  countDown();
}

void countDown()
{
  Serial2.print("CNTDOWN.");
  delay(10);
  for (int i = 3; i >= 0; i--){
    printNum(i, 1, 6, cyan);
    delay(1000);
    clearStrip(1);
  }
}

void clearStrip(int initialRow){
  for(int c = 0; c < 14; c++){
    for(int r = 0; r < 5; r++){
      strip.setPixelColor(PixelMatrice[initialRow + r][c], 0);
    }
  }
}

void clearLogicMatrice(){
  for(int i = 0; i < 20; i++){
    for(int j = 0; j < 14; j++) logicMatrice[i][j] = 0;
  }
}

void winnerCircle(uint32_t color1, uint8_t wait){
  bool exitVar = false;
  while(!exitVar){
    int i, j;
    
    i = 2;
    for(j = 4; j < 10; j++){
      strip.setPixelColor(PixelMatrice[i][9], 0);
      strip.setPixelColor(PixelMatrice[9-i][4], 0);
      i++;
      
      strip.setPixelColor(PixelMatrice[2][j], color1);
      strip.setPixelColor(PixelMatrice[7][13 - j], color1);
      strip.show();
      if(j != 9) delay(wait);
    }

    j = 4;
    for(i = 2; i < 8; i++){
      strip.setPixelColor(PixelMatrice[2][j], 0);
      strip.setPixelColor(PixelMatrice[7][13-j], 0);
      j++;
      
      strip.setPixelColor(PixelMatrice[i][9], color1);
      strip.setPixelColor(PixelMatrice[9-i][4], color1);
      strip.show();
      if(i != 7) delay(wait);
    }

    if(Serial.available() > 0){
      exitVar = true;
    }
    if(Serial1.available() > 0){
      command = Serial1.readStringUntil('.');
      if(command.equals("BReset")){
        exitVar = true;
        score1 = 0;
        score2 = 0;
      }
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


