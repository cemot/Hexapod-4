/*
 * Defines lib for servo control.
 *
 * Usage:
 * declare: ServoControllerBoard servoController = *new ServoControllerBoard(Serial1);
 *
 * Initialize the serial link in Setup() of the calling code, e.g. Serial1.begin(9600).
 * Then send commands: servoControler.Move(1, 500, 1000);
 */

#include <arduino.h>;
#include <HardwareSerial.h>;

#define NUMBER_OF_SERVOS 16

class ServoControllerBoard
{
    Stream& _stream; // member within class
    Stream& _debugStream; // member within class
    int positions[NUMBER_OF_SERVOS];

  public:
    ServoControllerBoard(Stream& serial, Stream& debugStream):
      _stream(serial), _debugStream(debugStream) // Need to initialise references before body
    {
    }

    // allows to set the positions of individual servos before calling Move(time);
    void SetServoPosition(int servoId, int position)
    {
      positions[servoId - 1] = position;
    }

    // Generates statement to move to servo position. Update positionarray externally.
    void MoveAll(int time) {
      _debugStream.print("MoveAll(t=");
      _debugStream.print(time);
      _debugStream.print(", pos=");
      for (int i = 1; i <= NUMBER_OF_SERVOS; i++) {
        //ServoPosition p = servoPositions[i];
        int position = positions[i];
        _debugStream.print("[");
        _debugStream.print(i);
        _debugStream.print(",");
        _debugStream.print(position);
        _debugStream.print("]");
        _stream.print("#");
        _stream.print(i);
        _stream.print("P");
        _stream.print(position);
      }

      _stream.print("T");
      _stream.println(time);
      _debugStream.println(")");

      delay(time);
    }

    // set an individual servo position
    void Move(int servo, int position, int time) {
      _stream.print("#");
      _stream.print(servo);
      _stream.print("P");
      _stream.print(position);
      _stream.print("T");
      _stream.println(time);
      delay(time);
    }

  private:
};

