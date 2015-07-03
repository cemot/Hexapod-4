/*
 * Test app for the servo controller board
 */

#include "ServoControllerBoard.h";

int ledPin = 13;
int loopCounter = 0;
ServoControllerBoard servoController = *new ServoControllerBoard(Serial1, Serial);

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  //val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  //int pulse = map(val, 180, 700, 700, 2000);

  loopCounter++;
  Serial.print("Loop: ");
  Serial.print(loopCounter);
  Serial.println();

  for (int id = 1; id <= NUMBER_OF_SERVOS; id++)
  {
    servoController.SetServoPosition(id, loopCounter * 2);
  }
  
  servoController.MoveAll(1000);

  while (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.write(inByte);
  }

  // read from port 0, send to port 1:
  while (Serial.available()) {
    int inByte = Serial.read();
    Serial1.write(inByte);
  }
}



