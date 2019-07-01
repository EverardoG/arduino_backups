#include <SoftwareSerial.h>

SoftwareSerial softSerial(8,9); 

void setup()
{
  softSerial.begin(9600);
}

void loop()
{
  softSerial.print('H');
  delay(1000);
  softSerial.print('L');
  delay(1000);
}
