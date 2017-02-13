#include <Arduino.h>

// Controller mappings
const byte buttonUp = 2;
const byte buttonRight = 3;
const byte buttonDown = 4;
const byte buttonLeft = 5;

const byte joystickUp = 6;
const byte joystickRight = 7;
const byte joystickDown = 8;
const byte joystickLeft = 9;

const byte buttonCenter = 10;
const byte buttonReset = 11;

// Store previous values to help replicate OnKeyDown event
bool buttonUpPrev = true;
bool buttonRightPrev = true;
bool buttonDownPrev = true;
bool buttonLeftPrev = true;
bool joystickUpPrev = true;
bool joystickRightPrev = true;
bool joystickDownPrev = true;
bool joystickLeftPrev = true;
bool buttonCenterPrev = true;
bool buttonResetPrev = true;


const int debounceDelay = 25;

#define NUM_CONTROL_PINS 10

// Row 0 : Pin mapping of controller inputs
// Row 1 : Previous values of controller inputs to help replicate OnKeyDown event
byte pinMap[2][NUM_CONTROL_PINS] = {{buttonUp,buttonRight,buttonDown,buttonLeft,joystickUp,joystickRight,joystickDown,joystickLeft,buttonCenter,buttonReset},
                                    {1,1,1,1,1,1,1,1,1,1} };

const char commandMap[][10] = {"BUp.","BRight.","BDown.","BLeft.","JUp.","JRight.","JDown.","JLeft.","BCenter.","BReset."};

void setup() {
  Serial.begin(9600);
  //Initialize pins
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(joystickUp, INPUT_PULLUP);
  pinMode(joystickRight, INPUT_PULLUP);
  pinMode(joystickDown, INPUT_PULLUP);
  pinMode(joystickLeft, INPUT_PULLUP);
  pinMode(buttonCenter, INPUT_PULLUP);
  pinMode(buttonReset, INPUT_PULLUP);

}

void loop() {

  // Get inputs OnKeyDown
  for(int i = 0; i < NUM_CONTROL_PINS; i++){
    if(digitalRead(pinMap[0][i]) == LOW){
      // If previous value is HIGH, send command to serial
      if(pinMap[1][i] == 1){
        Serial.print(commandMap[i]);
        pinMap[1][i] = 0;
      }
    }
  }

  delay(debounceDelay);

  // Reset inputs OnKeyUp
  for(int i = 0; i < NUM_CONTROL_PINS; i++){
    if(digitalRead(pinMap[0][i]) == HIGH){
      // If previous value is LOW, reset previous to HIGH
      if(pinMap[1][i] == 0)
        pinMap[1][i] = 1;
    }
  }

}
