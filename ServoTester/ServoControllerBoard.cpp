#include "Arduino.h"
#include "ServoControllerBoard.h"

int servoPortMapping[] = { 1, 2, 3, 10, 11, 12, 13, 14, 15, 18, 19, 20, 21, 22, 23, 28, 29, 30 };

ServoControllerBoard::ServoControllerBoard(Stream& serial, Stream& debugStream):
  _stream(serial), _debugStream(debugStream) // Need to initialise references before body
{
}


void ServoControllerBoard::Init() {
   for (int i = 1; i <= NUMBER_OF_SERVOS; i++) {
     this->SetServoPosition(i, INITIAL_POSITION);
   }
   this->MoveAll(200);
}

// allows to set the positions of individual servos before calling Move(time);
void ServoControllerBoard::SetServoPosition(int servoId, int position)
{
  positions[servoId] = position;
}

// Generates statement to move to servo position. Update positionarray externally.
void ServoControllerBoard::MoveAll(int time) {
  _debugStream.print("MoveAll(t=");
  _debugStream.print(time);
  _debugStream.print(", pos=");
  for (int i = 1; i <= NUMBER_OF_SERVOS; i++) {
    //ServoPosition p = servoPositions[i];
    int port = servoPortMapping[i - 1]; // zero based index
    int position = positions[i];
    //    _debugStream.print("[");
    _debugStream.print(i);
    _debugStream.print("@");
    _debugStream.print(port);
    _debugStream.print(">");
    _debugStream.print(position);
    _debugStream.print(",");
    _stream.print("#");
    _stream.print(port);
    _stream.print("P");
    _stream.print(position);
  }

  _stream.print("T");
  _stream.println(time);
  _debugStream.println(")");

  delay(time);
}

// set an individual servo position
void ServoControllerBoard::Move(int servo, int position, int time) {
  _stream.print("#");
  _stream.print(servo);
  _stream.print("P");
  _stream.print(position);
  _stream.print("T");
  _stream.println(time);
  delay(time);
}

