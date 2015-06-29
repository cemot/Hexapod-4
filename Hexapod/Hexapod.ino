// Sketch to control hexapod

#include <Servo.h>
#include "ServoControl.h";
#include "Movement.h";
#include <SoftwareSerial.h>
#include "MovementController.h";
#include "BodyMovement.h";
#include "InverseKinematics.h";

String command = ""; // Stores response of the HC-06 Bluetooth device
int ledPin = 13;
SoftwareSerial mySerial(10, 11); // RX, TX
MovementVector movementVector;
BodyMovementCalc bodyMovementCalc;
InverseKinematicsLimb* inverseKinematicsLimb = new InverseKinematicsLimb(15, 55, 90);

void setup() {
  Serial.begin(9600);
  Serial.println("Hexapod Lives! Pair 'hexapod' with passkey '1234'.");
  pinMode(ledPin, OUTPUT);
  mySerial.begin(9600);
  delay(10);
  mySerial.println("Hexapod Lives! Enter '?' for help.");

  ServoInit();
}

void loop() {
  // Read device output if available.
  if (mySerial.available()) {
    while (mySerial.available()) { // While there is more to be read, keep reading.
      command += (char)mySerial.read();
      delay(10);
    }

    ParseCommand(command);
    command = ""; // No repeats
  }

  // handle movement vector
  // calculate body base position Q
  double aRoll = movementVector.GetRoll() * 1.0; // todo
  double aPitch = movementVector.GetPitch() * 1.0; // todo
  endpoints* qEndpoints = bodyMovementCalc.CalculateQ(pEndpoints, aRoll, aPitch);

  // calculate leg endpoint S from the time/step multiplexer
  // NB for initial tests might start with static leg positions using a fixed offset from the body base position. Allows to shake and roll the body....

  // calculate leg differences T
  // T = Q - S
  point* test = new point(0, 110, 80);
  endpoints* T = new endpoints(test, test, test, test, test, test);

  // calculate leg angles alpha, beta, gamma using IK
  // T1 to T6
  // angle leg 1
  limbAngles* l1 = inverseKinematicsLimb->CalculateAngles(T->p1);
  // also calculate all other legs 2 to 6

  // send leg angles to MovementController

  // wait till executed and recalculate next step and position
  delay(100);
}

void ParseCommand(String command) {
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
    ServoMovement(StraightMovement);
  }
  else if (command == "b")
  {
    response = "Backward";
    movementVector.SetSurge(-1.0);
    ServoMovement(StraightMovement);
  }
  else if (command == "l")
  {
    response = "Yaw left";
    movementVector.SetYaw(1.0);
    ServoMovement(StraightMovement);
  }
  else if (command == "r")
  {
    response = "Yaw right";
    movementVector.SetYaw(-1.0);
    ServoMovement(StraightMovement);
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
  mySerial.println(response);
  mySerial.print("Movement Vector : ");
  mySerial.println(movementVector.ToString());
}

