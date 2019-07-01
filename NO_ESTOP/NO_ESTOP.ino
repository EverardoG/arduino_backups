#include <OrangutanLEDs.h>
#include <OrangutanAnalog.h>
#include <OrangutanMotors.h>

/*
 * OrangutanMotorExample for the 3pi robot, Orangutan LV-168, Orangutan SV-xx8,
 *   and Baby Orangutan B
 *
 * This example uses the OrangutanMotors library to drive
 * motors in response to the position of user trimmer potentiometer
 * and blinks the red user LED at a rate determined by the trimmer
 * potentiometer position.  It uses the OrangutanAnalog library to measure
 * the trimpot position, and it uses the OrangutanLEDs library to provide
 * limited feedback with the red user LED.
 *
 * http://www.pololu.com/docs/0J17/5.e
 * http://www.pololu.com
 * http://forum.pololu.com
 */

OrangutanAnalog analog;
OrangutanLEDs leds;
OrangutanMotors motors;
//int sensorPin = PB0;  //int motorSpeed /= sensor_value_forward;
int sensorPin2 =PD4;
int sensorPin3 = PD7;
//int sensorPin2 = PB0;
//int sensorPin3 = PB1;
//  delay(1000);
//int fakePin = PC1;
int motorSpeed1 = 0;
int motorSpeed2 = 0;
int forward = false;
int turnLeft = 0;
int turnRight = 0;
int onOffPin = PD2;
int onOff = 1;


void setup()               // run once, when the sketch starts
{
//pinMode(sensorPin, INPUT);
analog.setMode(MODE_10_BIT);
set_digital_input(onOffPin, PULL_UP_ENABLED);
}

void loop()                // run over and over again
{
 // analogWrite(fakePin, 0);
  int sensor_value_forward = pulseIn(sensorPin2, HIGH);
  int sensor_value_turn = pulseIn(sensorPin3, HIGH);
  
  if (sensor_value_forward > 1550)
  {
    motorSpeed1 = map(sensor_value_forward, 1550, 1900, 0, 255);
    motorSpeed2 = motorSpeed1;
  }
  else if (sensor_value_forward < 1450){
    motorSpeed1 = map(sensor_value_forward, 1100, 1450, 0, -255);
    motorSpeed2 = motorSpeed1;
  }
  else
  {
    motorSpeed1 = 0;
    motorSpeed2 = motorSpeed1;
  }
  if (sensor_value_turn > 1600){
    turnLeft = map(sensor_value_turn, 1600, 1900, 0, 255);
    turnRight = -turnLeft;
  }
  else if (sensor_value_turn < 1400) {
    turnLeft = map(sensor_value_turn, 1600, 1900, 0, 255);
    turnRight = -turnLeft;
  }
  else {
    turnRight = 0;
    turnLeft = -turnRight;
  }


    motorSpeed1 +=turnLeft;
    motorSpeed2 +=turnRight;  

    if(motorSpeed1 > 255) {
      motorSpeed1 = 255;
    }
    else if(motorSpeed1 < -255) {
      motorSpeed1 = -255;
    }
    if(motorSpeed2 > 255) {
      motorSpeed2 = 255;
    }
    else if(motorSpeed2 < -255) {
      motorSpeed2 = -255;
    }


  motors.setSpeeds(motorSpeed1, motorSpeed2);
}
