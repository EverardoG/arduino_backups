/* Title: Act Arduino
 * Description:
 * Robot Name: Tugboat
 * propellors - command input distance
 * when distance (pixy) of object is far, propellors speed fast
 * when distance (pixy) of object is near, propellors speed slow
 * rudders - command input angle
 * when angle (IR sensors) -60 degrees, rudders turn lot left
 * when angle (IR sensors) -30 degrees, rudders turn little left
 * when angle (IR sensors) 0 degrees, rudders still
 * when angle (IR sensors) 30 degrees, rudders turn little right
 * when angle (IR sensors) 60 degrees, rudders turn lot right
 */

// Libraries
#include <SoftwareSerial.h> //includes software serial library
#include <Servo.h>

Servo rudder;
int rudderPin = 5; //which pin is the rudder plugged into?
int rudderAngle = 0;
String input = "";

Servo prop;
int propPin = 6;
int objectDistance = 0;

Servo table;
int tablePin = 12;
int directionAngle = 0;

void setup() {
  // put your setup code here, to run once:
  //actSerial has same name in think and act arduinos
  //not attach the servos and motors. the motors act like continuous rotation servos
  Serial.begin(9600);
  rudder.attach(rudderPin);
  prop.attach(propPin);
  table.attach(tablePin);
  Serial.println("CAREFULL ROBOT IS RUNNING");
}

/////////////// MAIN LOOP ////////////////////////////////////
void loop() {
  // GET Operator Control Unit (OCU) Input: ocu---ocu---ocu---ocu---ocu---ocu---ocu---ocu---ocu---ocu---ocu---
  
  // angle inputted determines direction of rudders 
  // FIX THIS: direction of rudders does not depend on speed of motors?
  checkInput();
  setAngleToRudders(rudderAngle);
  setDistanceToSpeed(objectDistance);
  setAngleToTableMotor(directionAngle);
  delay(10);
}

/////////////// FUNCTIONS ////////////////////////////////////
void checkInput() { // input angle to control rudders
  //Serial.println("Input an angle a=*degrees from center to object* (from -30 to 30 degrees)");
  while (Serial.available() > 0) { // if any data sent through connection
    input = Serial.readString(); // set data equal to the string in serial
  }
  if (input.startsWith("a=")) {
    rudderAngle = input.substring(input.indexOf("=")+1).toInt(); // changes angleInput from character to integer
    directionAngle = input.substring(input.indexOf("=")+1).toInt();
    Serial.print("rudderAngle is set to: ");
    Serial.print(rudderAngle);
    Serial.print(" \t table angle is set to: ");
    Serial.println(directionAngle);
  input = "";
  }
  if (input.startsWith("d=")) {
    objectDistance = input.substring(input.indexOf("=")+1).toInt(); // changes distanceInput from character to integer
    Serial.print("objectDistance is set to: ");
    Serial.println(objectDistance);
  input = "";
  }
}

void setAngleToRudders (int angle) {
//  if (angle < -30 || angle > 30) {
//    Serial.println("Input angle is outside of the allowed interval");
//    rudderAngle = 0;
//  }
  //else {
    // turn rudders left and right depending on angle given
    // map the angle to a speed for the motor, speed mapped in microseconds
    int angletosend = map(angle,-30,30,13,73);
    rudder.write(angletosend);
  //}
}

void setDistanceToSpeed(int distance) {
//  if (distance < 0 || distance > 50){
//    Serial.println("Input angle is outside of the allowed interval");
//  }
//  else {
    // propellors speed dependent on distance of object
    // farther the object, faster the propellors; vice versa
    int microSec = map(distance,-50,50,1250,1750); // test speeds of different distances
    prop.writeMicroseconds(microSec);
//  }
}

void setAngleToTableMotor(int angle) {
  if(angle < -30 || angle > 30) {
    //Serial.println("Input angle is outside of the allowed interval");
  }
  else {
    //map the angle to a speed for the motor
    //this speed is mapped to a microseconds
    int microSec = map(angle,-30,30,1250,1750);
    table.writeMicroseconds(microSec);
  }
}
