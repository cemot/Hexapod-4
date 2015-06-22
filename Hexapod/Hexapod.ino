// Sketch to control hexapod

#include <Servo.h>
#include "ServoControl.h";
#include "Movement.h";


void setup() {
  // put your setup code here, to run once:
  // center all the legs to the initial position
  ServoInit();
}

void loop() {
  //StraightMovement straightMove;
  ServoMovement(StraightMovement);

  // put your main code here, to run repeatedly:
  delay(10);
}
