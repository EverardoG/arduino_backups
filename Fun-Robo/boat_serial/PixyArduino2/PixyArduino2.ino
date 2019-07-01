/*********************************************************************************************
*  Title: THINKlab Pixy Arduino Code
*  Description: This code is meant to allow the pixy Arduino to process data from the camera 
*  and pass it off to the next Arduino. Based on previous group's work and pixy "Hello World" 
*  code.
*  Robot Name: PixyTug
*  Hardware warnings: This code uses the ICSP port on the Arduino. Pixymon software is
*  useful for tracking what the camera sees, but the Arduino will stop processing if user is 
*  in raw video mode.
*  Written by Team Delta
*  ******************************************************************************************/
// TODO:
//  - Create PID controller based on outputs of pixy cam and IR sensors
//============================================================================================
// Load supporting Arduino Libraries
#include <SPI.h>
#include <Pixy.h>
#include <EasyTransfer.h>
//============================================================================================
// Create global variables, objects, constants
Pixy pixy;                        //Pixy object
EasyTransfer ET;                  //Transfer object
struct SEND_DATA_STRUCTURE        //Structure object for Arduino communication
{//variable definitions here for data to send - MUST BE EXACTLY THE SAME ON THE OTHER ARDUINOS
  int angle;};
SEND_DATA_STRUCTURE pixydata;     //Give structure an actual name
int xValue;                       //For centerpoint of block
int angle;                        //Used for remapping centerpoint to angle
int newLoopTime = 0;              //Counter variable
int oldLoopTime = 0;              //Counter variable
int controlLoopInterval = 100;    //Set control loop to 100 milliseconds
//============================================================================================
// Startup code to configure robot and set mission for launch.
//============================================================================================
void setup()
{
  ET.begin(details(pixydata), &Serial); //Begin communications between Arduinos
  pixy.init();                          //Initialize pixycam
  Serial.begin(9600);                   //Start Serial
  Serial.print("Starting...\n");
}
//============================================================================================
// Flight code to run continuously
//============================================================================================
void loop()
{
  int i;                                //variable needed for pixy functionality
  uint16_t blocks;                      //variable needed for pixy functionality
  char buf[32];                         //variable needed for pixy functionality
  
  //------------------------REAL TIME CONTROL LOOP STARTS HERE -------------------------------
  // real time clock control
  i++;                                  //needed for pixy functionality
  newLoopTime = millis();               //update time
  //run loop once every control loop interval
  if (newLoopTime - oldLoopTime >= controlLoopInterval)
  {
    blocks = pixy.getBlocks();          // grab blocks!
    Serial.print("Time: ");
    Serial.println(millis());
    Serial.print("Blocks? ");
    Serial.println(blocks);             //1 = blocks detected, 0 = no blocks
    oldLoopTime = newLoopTime;          //update time
    //if blocks are detected, find the x centerpoint and remap to angle. Update pixydata, send
    if (blocks)
    {
      xValue = pixy.blocks[0].x;        //give x center of object. blocks[0] is set config. 1
      pixydata.angle = map(xValue, 0, 319, -37, 37);  //remap to angle range
      Serial.print("Angle: ");
      Serial.println(pixydata.angle);
      ET.sendData();                    //send data to next Arduino
    }
  }
  // ---------------------REAL TIME CONTROL LOOP ENDS HERE -----------------------------------
}
