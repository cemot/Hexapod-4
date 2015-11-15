#include "Arduino.h"
#include "ServoControllerBoard.h"

// define the actual wiring of the servo / port mapping for the controller board
int servoPortMapping[] = { 26, 24, 25, 10, 11, 12, 13, 14, 15, 18, 19, 20, 21, 22, 23, 28, 29, 30 };
int positions[NUMBER_OF_SERVOS];

ServoControllerBoard::ServoControllerBoard(Stream& serial, Stream& debugStream):
  _stream(serial), _debugStream(debugStream) // Need to initialise references before body
{
}

// allows to set the positions of individual servos before calling Move(time);
void ServoControllerBoard::SetServoPosition(int servoId, int position)
{
  positions[servoId] = position;
      _debugStream.print("SetServoPosition ");
    _debugStream.print(servoId);
    _debugStream.print(", ");
    _debugStream.println(position);
}

void ServoControllerBoard::Init() {
   for (int i = 1; i <= NUMBER_OF_SERVOS; i++) {
     this->SetServoPosition(i, INITIAL_POSITION);
   }
   
   this->MoveAll(500);
}

// Generates statement to move to servo position. Update positionarray externally.
void ServoControllerBoard::MoveAll(int time) {
  _debugStream.print("MoveAll(t=");
  _debugStream.print(time);
  _debugStream.print(", pos=");
  for (int servoId = 1; servoId <= NUMBER_OF_SERVOS; servoId++) {
    int port = servoPortMapping[servoId - 1]; // zero based index
    int position = positions[servoId];
    positions[servoId] = (int) 0; // reset position so that it will only be output when actually set
    if(position < 400){
      continue; // position is not set after last MoveAll, so ignore.
    }
    
    _stream.print("#");
    _stream.print(port);
    _stream.print("P");
    _stream.print(position);
    _debugStream.print("#");
    _debugStream.print(port);
    _debugStream.print("P");
    _debugStream.print(position);
  }

  _stream.print("T");
  _stream.println(time);
  _debugStream.print("T");
  _debugStream.print(time);
  _debugStream.println(")");

  //delay(time);
}

// set an individual servo position
void ServoControllerBoard::Move(int servoId, int position, int time) {
  int port = servoPortMapping[servoId - 1]; // zero based index
  _debugStream.print("Move(t=");
  _debugStream.print(time);
  _debugStream.print(", pos=");   
  _debugStream.print(servoId);
  _debugStream.print("@");
  _debugStream.print(port);
  _debugStream.print(">");
  _debugStream.print(position);
  _debugStream.print(",");  
  _stream.print("#");
  _stream.print(port);
  _stream.print("P");
  _stream.print(position);
  _stream.print("T");
  _stream.println(time);
  delay(time);
}

