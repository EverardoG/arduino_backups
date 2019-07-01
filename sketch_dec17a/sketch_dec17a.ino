#define rcPin1 PC0   // Pin 8 Connected to CH1 of Transmitter;

#include <OrangutanLEDs.h>
#include <OrangutanAnalog.h>
#include <OrangutanMotors.h>
OrangutanAnalog analog;
OrangutanLEDs leds;
OrangutanMotors motors;

int ch1 = 0;  // Receiver Channel 1 PPM value

void setup() {
  pinMode(rcPin1, INPUT);
  Serial.begin(9600);
}

void loop() {

// Read in the length of the signal in microseconds
  ch1 = pulseIn(rcPin1, HIGH, 20000);  // (Pin, State, Timeout)
  if (ch1 > 0)
  {
   int motorSpeed = 255;
   motors.setSpeeds(motorSpeed, motorSpeed);
  }

  


  delay(500);
  

}
