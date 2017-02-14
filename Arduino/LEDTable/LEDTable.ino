#include <Tetris.h>
#include <Snake.h>

void setup() {
  // Initialize serial
	Serial.begin(9600);
	Serial1.begin(9600);  // To Nano, Game Controller
	Serial2.begin(9600);  // To Teensy, Audio
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
    else if(command.equals("SnakeGame")){
      playSnake();
    }
  }
}

void playTetris(){
  Serial.println("Playing Tetris...");
  Tetris tetris;
  while(!programStop()){
      tetris.Update();
  }
  Serial.println("...Exiting Tetris");
}

void playSnake(){
  Serial.println("Playing Snake...");
  Snake snake;
  while(!programStop()){
      snake.Update();
  }
  Serial.println("...Exiting Snake");
}

bool programStop(){
  if(Serial.available() > 0){
    String command = Serial.readStringUntil('.');
    if(command.equals("STOP"))
      return true;
  }
  return false;
}









