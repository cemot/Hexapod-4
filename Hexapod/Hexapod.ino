// Sketch to control hexapod

#include <Servo.h>
#include "ServoControl.h";
#include "Movement.h";
#include <SoftwareSerial.h>
#include "MovementController.h";

String command = ""; // Stores response of the HC-06 Bluetooth device
int ledPin = 13;
SoftwareSerial mySerial(10, 11); // RX, TX
MovementVector movementVector;

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
  // send to MovementController
  
  // check movement interval
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

