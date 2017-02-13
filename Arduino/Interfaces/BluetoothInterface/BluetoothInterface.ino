#include <Arduino.h>

// Connecting to HC 05/06
// Default password: 1234 OR 0000

String selection;

void setup() {
  Serial.begin(9600);            
  Serial3.begin(9600);              // Default communication rate of the Bluetooth module
}
void loop() {
  if(Serial3.available() > 0){       // Checks whether data is comming from the serial port
    selection = Serial3.readStringUntil('.');
    Serial.println(selection);
  }
}
