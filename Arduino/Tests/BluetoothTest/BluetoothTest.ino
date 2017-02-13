#include <Arduino.h>

#define ledPin 22

int state = 0;
// Connecting to HC 05/06
// Default password: 1234 OR 0000
void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);            
  Serial1.begin(9600);              // Default communication rate of the Bluetooth module
}
void loop() {
  if(Serial1.available() > 0){       // Checks whether data is comming from the serial port
    state = Serial1.read();          // Reads the data from the serial port
  }
  if (state == '0') {
    digitalWrite(ledPin, LOW);      // Turn LED OFF
    Serial.println("LED: OFF");    
    Serial1.println("LED: OFF");     
    state = 0;
  }
  else if (state == '1') {
    digitalWrite(ledPin, HIGH);     // Turn LED ON
    Serial.println("LED: ON");    
    Serial1.println("LED: ON");
    state = 0;
  } 
}
