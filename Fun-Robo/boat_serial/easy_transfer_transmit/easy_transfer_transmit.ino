#include <EasyTransfer.h>

//create object
EasyTransfer ET; 

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int greenLEDval = 0;
  int redLEDval = 0;
  int blueLEDval = 0;
};

//give a name to the group of data
SEND_DATA_STRUCTURE actdata;

void setup(){
  Serial.begin(9600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(actdata), &Serial);  
}

void loop(){
  // ask user for input on LED values
  Serial.println("Pick a green LED value");
  while (Serial.available() == 0) {}; // do nothing until input is recieved
  actdata.greenLEDval = Serial.readString().toInt();

  Serial.println("Pick a red LED value");
  while (Serial.available() == 0) {}; // do nothing until input is recieved
  actdata.redLEDval = Serial.readString().toInt();

  Serial.println("Pick a blue LED value");
  while (Serial.available() == 0) {}; // do nothing until input is recieved
  actdata.blueLEDval = Serial.readString().toInt();

  //send the data
  ET.sendData();
  
  delay(1000);
}
