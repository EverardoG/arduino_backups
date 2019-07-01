
#include <SoftwareSerial.h>

SoftwareSerial softSerial(8,9); 

const int ledPin =  13;  

void setup()
{
  softSerial.begin(9600);
  pinMode(ledPin, OUTPUT);
  
  digitalWrite(ledPin, LOW);
}

void loop()
{
  char InChar;
  
  InChar = softSerial.read();
  
  if(InChar == 'H') 
  {
    digitalWrite(ledPin, HIGH); 
  }
  else if(InChar == 'L')
  {
    digitalWrite(ledPin, LOW);
  }  
  delay(1);
}
