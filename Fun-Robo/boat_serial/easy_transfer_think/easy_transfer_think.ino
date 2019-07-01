#include <EasyTransfer.h>

//create EasyTransfer object for receiving data from SENSE
EasyTransfer SENSE;

//create EasyTransfer object for sending data to ACT
EasyTransfer ACT;

// initialize time loop variables
unsigned long oldLoopTime = 0;
unsigned long newLoopTime = 0;
unsigned long cycleTime = 0;
const long controlLoopInterval = 1000;

struct RECEIVE_SENSE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int greenLEDval = 0;
  int redLEDval = 0;
  int blueLEDval = 0;
};

struct SEND_ACT_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int greenLEDval = 0;
  int redLEDval = 0;
  int blueLEDval = 0;
  };

//give a name to the SENSE group of data
RECEIVE_SENSE_DATA_STRUCTURE sensedata;

//give a name to the ACT group of data
SEND_ACT_DATA_STRUCTURE actdata;

void setup(){
  Serial.begin(9600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
  SENSE.begin(details(sensedata), &Serial);
  ACT.begin(details(actdata), &Serial);
}

void loop(){
  //------------------------REAL TIME CONTROL LOOP STARTS HERE ---------------------
  // real time clock control
  newLoopTime = millis();
  if (newLoopTime - oldLoopTime >= controlLoopInterval){
  oldLoopTime = newLoopTime;
  
    //check and see if a data packet has come in. 
    if(SENSE.receiveData()){     
      //set all values appropriately
      actdata.redLEDval = sensedata.redLEDval;
      actdata.greenLEDval = sensedata.greenLEDval;
      actdata.blueLEDval = sensedata.blueLEDval;

      // pass on values to the ACT arduino
      ACT.sendData();
    }
    
  // ---------------------REAL TIME CONTROL LOOP ENDS HERE -------------------------
  }

// Hopefully this delay is unnecessary once this real time control loop works
//  //you should make this delay shorter then your transmit delay or else messages could be lost
//  delay(250);
}
