/*
 * Test app for the servo controller board
 */

#include "ServoControllerBoard.h";
#include "ServoNormalisation.h";
#define STEPS 4
//#define GROUP_MEMBERS 3

#define M0 1000
#define N 1100
#define X0 1500

#define J2L 1300
#define J2R 1300

#define J3L 1550
#define J3R 650

int pulses[6][3][4] = {
  // leg 1
  {
    {X0, N, M0, N}, //S1
    {N, N, J2L, N}, //S2
    {N, J3L, J3L, J3L} //S3
  },

  // leg 2
  {
    {M0, N, X0, N}, //S1
    {J2L, N, N, N}, //S2
    {J3L, J3L, J3L, N} //S3
  },

  // leg 3
  {
    {X0, N, M0, N}, //S1
    {N, N, J2L, N}, //S2
    {N, J3L, J3L, J3L} //S3
  },

  // leg 4
  {
    {X0, N, M0, N}, //S1
    {J2R, N, N, N}, //S2
    {J3R, J3R, J3R, N} //S3
  },

  // leg 5
  {
    {M0, N, X0, N}, //S1
    {N, N, J2R, N}, //S2
    {N, J3R, J3R, J3R} //S3
  },

  // leg 6
  {
    {X0, N, M0, N}, //S1
    {J2R, N, N, N}, //S2
    {J3R, J3R, J3R, N} //S3
  }
};

int ledPin = 13;
ServoControllerBoard _servoControllerBoard = *new ServoControllerBoard(Serial1, Serial);
int pulse1;
int pulse2;

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  delay(200);
  _servoControllerBoard.Init();
}

void loop() {
  for (int loopCounter = 0; loopCounter < STEPS; loopCounter++) {
    Serial.print("Step: ");
    Serial.print(loopCounter);
    Serial.println();

    for (int leg = 1; leg <= 6; leg++)
    {
      for (int joint = 1 ; joint <= 3; joint++)
      {
        int pulse = pulses[leg - 1][joint - 1][loopCounter];
        int servoId = (leg - 1) * 3 + joint;
        Serial.print("  Leg: ");
        Serial.print(leg);
        Serial.print("  J: ");
        Serial.print(joint);
        Serial.print("  ServoId: ");
        Serial.print(servoId);
        Serial.print("  P: ");
        Serial.println(pulse);

        _servoControllerBoard.SetServoPosition(servoId, pulse);
      }

      Serial.println();
    }

    _servoControllerBoard.MoveAll(300);
    Serial.println();

    while (Serial1.available()) {
      int inByte = Serial1.read();
      Serial.write(inByte);
    }

    // read from port 0, send to port 1:
    while (Serial.available()) {
      int inByte = Serial.read();
      Serial1.write(inByte);
    }

    delay(20);
  }
}



