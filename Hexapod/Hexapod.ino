// Sketch to control hexapod

#include <Servo.h>
#include "ServoControl.h";
#include "Movement.h";
#include <SoftwareSerial.h>

String command = ""; // Stores response of the HC-06 Bluetooth device
int ledPin = 13;
SoftwareSerial mySerial(10, 11); // RX, TX

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
    while(mySerial.available()) { // While there is more to be read, keep reading.
      command += (char)mySerial.read();
      delay(10);
    }

    ParseCommand(command);
    command = ""; // No repeats
   }
   
  // put your main code here, to run repeatedly:
  delay(10);
}

void ParseCommand(String command){
  String response = "";
  digitalWrite(13, LOW);
  bool stopMovement = true;
  if(command == "?" || command == "")
  {
    response +="Commands:\r\n";
    response +="f: forward\r\n";
    //response +="b: backward\r\n";
    //response +="l: left\r\n";
    //response +="r: right\r\n";
    response +="s: stop\r\n";
    response +="x: light led 13\r\n";
    response +="?: display this help\r\n";
  }
  else if(command == "x")
  {
    response = "Lights on!";
    digitalWrite(13, HIGH);  
  }
  else if(command == "f")
  {
    response = "Forward";
    ServoMovement(StraightMovement);
  }
  else if (command == "s")
  {
    stopMovement = true;
    response = "Stop";
  }
  
  response +="\r\n";
  mySerial.println(response);
}
