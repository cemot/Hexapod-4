/*
Performs servo initialization and control
*/

#include <Servo.h>
#include <arduino.h>
#include "LegMovementStruct.h";


int servoPins[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 };
Servo servo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

void ServoInit()
{
  servo.attach(9);  // attaches the servo on pin 9 to the servo object
  
  // TODO: initialize the servo control board
}

void ServoMovement(PodMovementStep steps[])
{
  int arrayLength = (sizeof(steps) / sizeof(PodMovementStep)) - 1;
  int i;

  for (i = 0; i < arrayLength; i = i + 1)
  { 
    int lm;
    for(lm = 0; lm < 6; lm = lm + 1)
    {
      int j;
      char commandSequence[] = "";
      for(j = 0; j < 3; j=j+1)
      {
        // NB Combine all 18 servo commands into 1 big sequence....
        int servoId = lm * 3 + j;
        // determine servo PIN
        //servo=xxx                        // get the servo command..
        //myservo.write(pos);              
        delay(10);                       // waits 15ms for the servo to reach the position
      }
      
      // execute command sequence; send to servo controller board
    }
  }
}
