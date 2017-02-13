#include <Tetris.h>

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


void setup() {
  // Initialize serial
	Serial.begin(9600);
	Serial1.begin(9600);  // To Nano, Game Controller
	Serial2.begin(9600);  // To Teensy, Audio

  // Play Tetris Theme
	Serial2.print("THEME.TETRIS.");
}

/*
Bluetooth commands:
TetrisGame.
SnakeGame.
TronGame.
PongGame.
*/

void loop() {
  if(Serial.available() > 0){
    String command = Serial.readStringUntil('.');
    if(command.equals("TetrisGame")){
    playTetris();
    }
  }
}


void playTetris(){
  Serial.println("Playing Tetris...");
  
  String command;
  Tetris tetris;
  while(!command.equals("STOP")){
    if(Serial.available() > 0){
      command = Serial.readStringUntil('.');
    }
    else{
      tetris.Update();
    }
  }
}
