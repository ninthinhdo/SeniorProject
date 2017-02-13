#include <Arduino.h>

String input;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial2.available() > 0){
    input = Serial2.readStringUntil('.');
    Serial.println(input);
  }
}
