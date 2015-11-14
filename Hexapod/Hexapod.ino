// Sketch to control hexapod

#include <SoftwareSerial.h>
#include "MovementController.h";
#include "BodyMovement.h";

String command = ""; // Stores response of the HC-06 Bluetooth device
int ledPin = 13;
//SoftwareSerial mySerial(10, 11); // RX, TX
MovementVector movementVector;
ServoControllerBoard _servoControllerBoard = *new ServoControllerBoard(Serial1, Serial);
BodyMovementCalc bodyMovementCalc = *new BodyMovementCalc(_servoControllerBoard);

void setup() {
  Serial.begin(9600);
  Serial.println("Hexapod Lives! Pair 'hexapod' with passkey '1234'.");
  pinMode(ledPin, OUTPUT);
  Serial1.begin(9600);
  delay(200);
  //Serial1.println("Hexapod Lives! Enter '?' for help.");
  _servoControllerBoard.Init();
}

void loop() {
  // Read device output if available.
  if (Serial.available()) {
    while (Serial.available()) { // While there is more to be read, keep reading.
      command += (char)Serial.read();
      delay(10);
    }

    ParseCommandUpdateMovementVector(command);
    command = ""; // No repeats
  }

  while (Serial1.available()) { // While there is more to be read, keep reading.
    Serial.print(Serial1.read());
  }


  // handle movement vector
  // calculate body base position Q
  double aRoll = movementVector.GetRoll() * 1.0; // todo
  double aPitch = movementVector.GetPitch() * 1.0; // todo

  // endpoints* qEndpoints = bodyMovementCalc.CalculateQ(pEndpoints, aRoll, aPitch);
  bodyMovementCalc.Move(); // calculate new steps and send them to the servo controller.

  // wait till executed and recalculate next step and position
  delay(50);  // TODO: might make a more advanced timing mechanism
}

void ParseCommandUpdateMovementVector(String command) {
  String response = "";
  digitalWrite(13, LOW);
  bool stopMovement = true;
  if (command == "?" || command == "")
  {
    response += "Commands:\r\n";
    response += "f: forward\r\n";
    response += "b: backward\r\n";
    response += "l: left\r\n";
    response += "r: right\r\n";
    response += "s: stop\r\n";
    response += "<: roll left\r\n";
    response += ">: roll right\r\n";
    response += "[: pitch front\r\n";
    response += "]: pitch rear\r\n";
    response += "x: light led 13\r\n";
    response += "?: display this help\r\n";
  }
  else if (command == "x")
  {
    response = "Lights on!";
    digitalWrite(13, HIGH);
  }
  else if (command == "f")
  {
    response = "Forward";
    movementVector.SetSurge(1.0);
  }
  else if (command == "b")
  {
    response = "Backward";
    movementVector.SetSurge(-1.0);
  }
  else if (command == "l")
  {
    response = "Yaw left";
    movementVector.SetYaw(1.0);
  }
  else if (command == "r")
  {
    response = "Yaw right";
    movementVector.SetYaw(-1.0);
  }
  else if (command == "<")
  {
    response = "Roll left";
    movementVector.SetRoll(-1.0);
  }
  else if (command == ">")
  {
    response = "Roll right";
    movementVector.SetRoll(1.0);
  }
  else if (command == "[")
  {
    response = "Pitch front";
    movementVector.SetPitch(1.0);
  }
  else if (command == "]")
  {
    response = "Pitch rear";
    movementVector.SetPitch(-1.0);
  }  else if (command == "s")
  {
    stopMovement = true;
    response = "Stop";
    movementVector.SetStop();
  }
  else if (command == "p")
  {
    String p = String("#MV:S:2.5;Y:0.0;H:0.0;r:1.2;p:0.0;y:-1.5;");
    movementVector.Parse(p);
  }

  response += "\r\n";
  Serial.println(response);
  Serial.print("Movement Vector : ");
  Serial.println(movementVector.ToString());
}

