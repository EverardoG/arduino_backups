/* Title: Act Arduino
   Description:
   Robot Name: Tugboat
   propellors - command input distance
   when distance (pixy) of object is far, propellors speed fast
   when distance (pixy) of object is near, propellors speed slow
   rudders - command input angle
   when angle (IR sensors) -60 degrees, rudders turn lot left
   when angle (IR sensors) -30 degrees, rudders turn little left
   when angle (IR sensors) 0 degrees, rudders still
   when angle (IR sensors) 30 degrees, rudders turn little right
   when angle (IR sensors) 60 degrees, rudders turn lot right
*/

// Libraries
#include <EasyTransfer.h>
#include <SoftwareSerial.h> //includes software serial library
#include <Servo.h>

// Creating servo objects
Servo rudder;
int rudderPin = 5;
int rudderAngle = 0;
String input = "";

Servo prop;
int propPin = 6;
int objectDistance = 0;

Servo table;
int tablePin = 12;
int directionAngle = 0;

// initialize time loop variables
unsigned long oldLoopTime = 0;
unsigned long newLoopTime = 0;
unsigned long cycleTime = 0;
const long controlLoopInterval = 100;

//Creating Easy Transfer object
EasyTransfer ET;

struct RECEIVE_DATA_STRUCTURE
{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int angle;
};
//Give struct an actual name
RECEIVE_DATA_STRUCTURE pixydata;

void setup() {
  // put your setup code here, to run once:
  //actSerial has same name in think and act arduinos
  //not attach the servos and motors. the motors act like continuous rotation servos
  Serial.begin(9600);
  rudder.attach(rudderPin);
  prop.attach(propPin);
  table.attach(tablePin);
  ET.begin(details(pixydata), &Serial);
  Serial.println("CAREFULL ROBOT IS RUNNING");
}

/////////////// MAIN LOOP ////////////////////////////////////
void loop() {

  // angle inputted determines direction of rudders
  // FIX THIS: direction of rudders does not depend on speed of motors?

  //-------------------------REAL TIME CONTROL LOOP STARTS HERE ------------------------
  // real time clock control
  newLoopTime = millis();
  if (newLoopTime - oldLoopTime >= controlLoopInterval) {
    oldLoopTime = newLoopTime;

    if (ET.receiveData()) {
      setAngleToRudders(-pixydata.angle);
      setAngleToTableMotor(-pixydata.angle);
      Serial.print("Angle Received: "); Serial.println(pixydata.angle);
    }
  }
}

//TODO: Implement Speed Control
//setDistanceToSpeed(objectDistance);

/////////////// FUNCTIONS ////////////////////////////////////
void setAngleToRudders (int angle) {
  //  if (angle < -30 || angle > 30) {
  //    Serial.println("Input angle is outside of the allowed interval");
  //    rudderAngle = 0;
  //  }
  //else {
  // turn rudders left and right depending on angle given
  // map the angle to a speed for the motor, speed mapped in microseconds
  int angletosend = map(angle, -30, 30, 13, 73);
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
  int microSec = map(distance, -50, 50, 1250, 1750); // test speeds of different distances
  prop.writeMicroseconds(microSec);
  //  }
}

void setAngleToTableMotor(int angle) {
  if (angle < -30 || angle > 30) {
    //Serial.println("Input angle is outside of the allowed interval");
  }
  else {
    //map the angle to a speed for the motor
    //this speed is mapped to a microseconds
    int microSec = map(angle, -30, 30, 1250, 1750);
    table.writeMicroseconds(microSec);
  }
}
