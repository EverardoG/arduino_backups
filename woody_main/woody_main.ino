#include <OrangutanLEDs.h>
#include <OrangutanAnalog.h>
#include <OrangutanMotors.h>

OrangutanAnalog analog;
OrangutanLEDs leds;
OrangutanMotors motors;

int elePin = PD7;
int thrPin = PD4;
int elePinSensorVal;
int thrPinSensorVal;
int right_mtr_cmd;
int left_mtr_cmd;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  analog.setMode(MODE_10_BIT);

}

void loop() {
  // put your main code here, to run repeatedly:
  elePinSensorVal = pulseIn(elePin,HIGH); //right
  thrPinSensorVal = pulseIn(thrPin,HIGH); //left
  
  //Serial.print("Thr Value: "); Serial.print(thrPinSensorVal); Serial.print(" | "); Serial.print("Ele Value: "); Serial.println(elePinSensorVal);

  // thr mid - 1377
  // ele mid - 1380

  // thr max - 1812
  // ele max - 1818

  // thr min - 978
  // ele min - 1003

// SOFT CODED
   left_mtr_cmd = mapMotor(thrPinSensorVal, 1812, 978, 1277, 1477);
   right_mtr_cmd = mapMotor(elePinSensorVal, 1818, 1003, 1280, 1480);


// HARD CODED
//  left_mtr_cmd = mapMotor(thrPinSensorVal);
//  right_mtr_cmd = mapMotor(elePinSensorVal);

// print motor commands
   //Serial.print("Left Motor Val: "); Serial.print(left_mtr_cmd); Serial.print(" | "); Serial.print("Right Motor Val: "); Serial.println(right_mtr_cmd);

  // send motor commands
  motors.setSpeeds(left_mtr_cmd, right_mtr_cmd);
  

  delay(10);
}

// useful functions go here

// hard coded motor mapping
int mapMotor(int sensor_val){
  // INPUT:
  // sensor_val (int) - the pwm value read in from the radio
  // OUTPUT:
  // (int) mtr_cmd - command pwm to send motor
  int mtr_cmd;

  if (sensor_val > 1800){
    // full speed forward
    mtr_cmd = 255;
    }

  else if(sensor_val<1800 && sensor_val>1500){
    // map speed for forward
    mtr_cmd = map(sensor_val, 1500, 1800, 0, 255);
    }

  else if(sensor_val<=1500 && sensor_val >= 1300){
    // dead zone, don't move
    mtr_cmd = 0;
    }

  else if(sensor_val < 1300 && sensor_val > 1010){
    // map speed backwards
    mtr_cmd = map(sensor_val, 1010, 1300, -255, 0);
    }
    
  else{
    // full speed backwards
    mtr_cmd = -255;}

  // return the command
  return mtr_cmd;
  }

// smarter motor mapping
int mapMotor(int sensor_val, int sensor_max, int sensor_min, int sensor_dead_min, int sensor_dead_max){
  // INPUT:
  // sensor_val (int) - the pwm value read in from the radio
  // sensor_max (int) - the max pwm value read in
  // sensor_min (int) - min pwm value read in
  // sensor_dead_min (int) - min pwm value that counts as dead zone
  // sensor_dead_max (int) - max pwm value that counts as dead zone
  // OUTPUT:
  // (int) mtr_cmd - command pwm to send motor
  int mtr_cmd;

  if (sensor_val > sensor_max){
    // full speed forward
    mtr_cmd = 255;
    }

  else if(sensor_val<sensor_max && sensor_val>sensor_dead_max){
    // map speed for forward
    mtr_cmd = map(sensor_val, sensor_dead_max, sensor_max, 0, 255);
    }

  else if(sensor_val<=sensor_dead_max && sensor_val >= sensor_dead_min){
    // dead zone, don't move
    mtr_cmd = 0;
    }

  else if(sensor_val < sensor_dead_min && sensor_val > sensor_min){
    // map speed backwards
    mtr_cmd = map(sensor_val, sensor_min, sensor_dead_min, -255, 0);
    }
    
  else{
    // full speed backwards
    mtr_cmd = -255;}

  // return the command
  return mtr_cmd;
  }
  
