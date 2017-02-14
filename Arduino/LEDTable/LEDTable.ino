#include <Arduino.h>
#include <Tetris.h>
#include <Snake.h>
#include <AudioSpectrum.h>

#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
#include "avr/power.h"
#endif
#include "avr/pgmspace.h"

#define PIN 44
Adafruit_NeoPixel strip = Adafruit_NeoPixel(280, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  strip.begin();
  strip.setBrightness(32);
  strip.clear();
  
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

void loop()
{
  if(Serial.available() > 0){
    String command = Serial.readStringUntil('.');
    if(command.equals("TetrisGame")){
      playTetris();
    }
    else if(command.equals("SnakeGame")){
      playSnake();
    }
    else if(command.equals("AudioSpectrum")){
      audioSpectrum();
    }
  }
}

void playTetris(){
  Serial.println("Initializing Tetris...");
  Tetris tetris;
  while(!programStop()){
      tetris.Update();
  }
  Serial.println("...Exiting Tetris");
}

void playSnake()
{
  Serial.println("Initializing Snake...");
  Snake snake;
  while(!programStop()){
      snake.Update();
  }
  Serial.println("...Exiting Snake");
}

void audioSpectrum()
{
  Serial.println("Initializing Audio Spectrum...");
  AudioSpectrum spectrum;
  while(!programStop()){
      spectrum.Update();
  }
  Serial.println("...Exiting Audio Spectrum");
}


bool programStop()
{
  if(Serial.available() > 0){
    String command = Serial.readStringUntil('.');
    if(command.equals("STOP")){
      Serial2.print("STOP.");
      return true;
    }
  }
  return false;
}









