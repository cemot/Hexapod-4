/*
 * Defines lib for servo control.
 *
 * Usage:
 * declare: ServoControllerBoard servoController = *new ServoControllerBoard(Serial1);
 *
 * Initialize the serial link in Setup() of the calling code, e.g. Serial1.begin(9600).
 * Then send commands: servoControler.Move(1, 500, 1000);
 */
#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include <arduino.h>;
#include <HardwareSerial.h>;

#define NUMBER_OF_SERVOS 18
#define INITIAL_POSITION 1200

class ServoControllerBoard
{
  public:
    ServoControllerBoard(Stream& serial, Stream& debugStream);

    void Init();
    
    // allows to set the positions of individual servos before calling Move(time);
    void SetServoPosition(int servoId, int position);

    // Generates statement to move to servo position. Update positionarray externally.
    void MoveAll(int time);

    // set an individual servo position
    void Move(int servo, int position, int time);

  private:
    Stream& _stream;
    Stream& _debugStream;
    int positions[NUMBER_OF_SERVOS + 1];
};
#endif
