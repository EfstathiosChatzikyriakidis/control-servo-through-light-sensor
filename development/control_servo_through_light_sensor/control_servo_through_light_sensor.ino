/*
 *  Control Servo Through Light Sensor (e.g. Photoresistor).
 *
 *  Copyright (C) 2010 Efstathios Chatzikyriakidis (stathis.chatzikyriakidis@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// include library for servo.
#include <Servo.h>

Servo myServo; // create servo object to control a servo.

const int servoPin = 9;  // the pin number (PWM) for the servo.
const int sensorPin = 0; // the pin number for the input sensor.

// current and previous values for servo device.
int valServo = 0;
int oldValue = 0;

// the following values may change according to the light sensor.
// perform a calibration with pure dark, and pure light at first.

const int lightMin = 170; // set the appropriate value of the light sensor.
const int lightMax = 512; // set the appropriate value of the light sensor.

const int LIGHT_SENSE = 5; // difference level sensitivity value.
const long delayTime = 15; // servo movement delay time in millis.

// startup point entry (runs once).
void setup () {
  // set sensor as input.
  pinMode(sensorPin, INPUT);

  // attach the servo on a pin.
  myServo.attach(servoPin);
}

// loop the main sketch.
void loop () {
  // get the value from the light sensor.
  int valServo = analogRead(sensorPin);

  // map the value to the min, max of the servo.
  valServo = map (valServo, lightMin, lightMax, 0, 179);

  // ensure that the value is between min, max of the servo.
  valServo = constrain(valServo, 0, 179);

  // move servo only if light changes enough.
  if (abs(valServo - oldValue) > LIGHT_SENSE) {
    // move the servo.
    myServo.write(valServo);

    // keep the last value.
    oldValue = valServo;
  }
  
  // wait some time the servo to move.
  delay(delayTime);
}
