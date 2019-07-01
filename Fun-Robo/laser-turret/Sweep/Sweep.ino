/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

// initialize connection with laser and its state variable
int laserState = LOW;
const int laserPin = 11;

// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(12);  // attaches the servo on pin 13 to the servo object
  pinMode(laserPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //laserState = HIGH; // turn on the laser
  
  digitalWrite(laserPin,laserState);
  for (pos = 0; pos <= 180; pos += 5) { // goes from 0 degrees to 180 degrees
    // in steps of 5 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.print("Servo Angle");
    Serial.println(pos);
    delay(500);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 5) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.print("Servo Angle");
    Serial.println(pos);
    delay(500);                       // waits 15ms for the servo to reach the position
  }
}

