#include <EasyTransfer.h>

//create object
EasyTransfer ACT; 

// initializing pins for LEDs
int greenLEDpin = 6;
int redLEDpin = 5;
int blueLEDpin = 3;

// initialize time loop variables
unsigned long oldLoopTime = 0;
unsigned long newLoopTime = 0;
unsigned long cycleTime = 0;
const long controlLoopInterval = 1000;

struct RECEIVE_ACT_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int greenLEDval = 0;
  int redLEDval = 0;
  int blueLEDval = 0;
};

//give a name to the group of data
RECEIVE_ACT_DATA_STRUCTURE actdata;

void setup(){
  Serial.begin(9600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
  ACT.begin(details(actdata), &Serial);
  
  pinMode(13, OUTPUT);
  pinMode(greenLEDpin, OUTPUT);
  pinMode(redLEDpin, OUTPUT);
  pinMode(blueLEDpin, OUTPUT);
  
}

void loop(){
  //------------------------REAL TIME CONTROL LOOP STARTS HERE ---------------------
  // real time clock control
  newLoopTime = millis();
  if (newLoopTime - oldLoopTime >= controlLoopInterval){
  oldLoopTime = newLoopTime;
  
    //check and see if a data packet has come in. 
    if(ACT.receiveData()){
      // turn LEDs to appropriate values
      analogWrite(greenLEDpin,actdata.greenLEDval);
      analogWrite(redLEDpin,actdata.redLEDval);
      analogWrite(blueLEDpin,actdata.blueLEDval);
    }
    
  // ---------------------REAL TIME CONTROL LOOP ENDS HERE -------------------------
  }

// Hopefully this delay is unnecessary once this real time control loop works
//  //you should make this delay shorter then your transmit delay or else messages could be lost
//  delay(250);
}
