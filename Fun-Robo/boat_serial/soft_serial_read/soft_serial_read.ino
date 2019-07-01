#include <SoftwareSerial.h> // getting software serial library

SoftwareSerial softSerial(8,9);  // creating softwareserial object

const int greenLedPin =  7;  // pin for LED

void setup()
{
  Serial.begin(9600); // begin communication with serial monitor
  softSerial.begin(9600); // begining soft serial communication
  pinMode(greenLedPin, OUTPUT); //setting LED pin to digital output
  
  digitalWrite(greenLedPin, LOW); // writing LED to off
}

void loop()
{
  char InChar; // creating variable for reading from master arduino
  
  InChar = softSerial.read(); // reading softserial input
//  Serial.println(InChar);

  // setting LED on or off based on softserial input
  if(InChar == 'H') 
  {
    digitalWrite(greenLedPin, HIGH); 
    Serial.println("high");
  }
  else if(InChar == 'L')
  {
    digitalWrite(greenLedPin, LOW);
    Serial.println("low");
  }  
  delay(1);
}
