//  HB-25 Library Test
//
//  Version:  1.1
//  Date:     10th December 2015
//
//  Valid speed ranges for the forwardAtSpeed and reverseAtSpeed methods are
//  0 (stop) to 500 (maximum speed). For rampToSpeed and moveAtSpeed you can use from -500 (full
//  reverse) to 500 (full forward). As before, a speed of 0 will stop the motor.
//
//	Remember to call the begin() method in setup().
//
//  Adapted from a sketch by zoomkat 10-22-11 serial servo test

#include <Servo.h>                      //  You need to include Servo.h as it is used by the HB-25 Library
#include "HB25MotorControl.h"

const byte controlPin = 9;              //  Pin Definition
String readString;

HB25MotorControl motorControl(controlPin);

void setup() {
  Serial.begin(9600);
  Serial.println("HB-25 Motor Control Library Test");
  Serial.println("Enter a speed between -500 and 500.");
  Serial.println("A negative speed will reverse the motor direction. 0 will stop.");
  motorControl.begin();
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();             //  Gets one byte from the serial buffer
    readString += c;
    delay(2);                           //  Slow looping to allow buffer to fill with the next character
  }

  if (readString.length() > 0) {
    Serial.print("\nString entered: ");
    Serial.print(readString);        // Echo captured string
    int n = readString.toInt();        // Convert readString into a number
    n = constrain(n, -500, 500);

    if (n > 0) {
      Serial.print("Set Forward Speed: ");
    } else if (n < 0) {
      Serial.print("Set Reverse Speed: ");
    } else {
      Serial.print("Stop Motor. Speed: ");
    }
    Serial.println(n);
    motorControl.moveAtSpeed(n);

    readString = "";                  //  Empty string for the next input
  }
}