#include <Arduino.h>

String command; 

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  if(Serial1.available() > 0){
    command = Serial1.readStringUntil('\n');

    //Serial.println(command.length());
    if(command.equals("BUp\r"))
      Serial.println(command);
  }
  
}
