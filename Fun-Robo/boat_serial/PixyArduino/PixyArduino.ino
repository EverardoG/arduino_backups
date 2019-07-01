//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// This sketch is a good place to start if you're just getting started with
// Pixy and Arduino.  This program simply prints the detected object blocks
// (including color codes) through the serial console.  It uses the Arduino's
// ICSP port.  For more information go here:
//
// http://cmucam.org/projects/cmucam5/wiki/Hooking_up_Pixy_to_a_Microcontroller_(like_an_Arduino)
//
// It prints the detected blocks once per second because printing all of the
// blocks for all 50 frames per second would overwhelm the Arduino's serial port.
//

#include <SPI.h>
#include <Pixy.h>
#include <EasyTransfer.h>

// This is the main Pixy object
Pixy pixy;
// Transfer object
EasyTransfer ET;

struct SEND_DATA_STRUCTURE
{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int angle;
};
//Give struct an actual name
SEND_DATA_STRUCTURE pixydata;

int xValue;
int angle;
int newLoopTime = 0;
int oldLoopTime = 0;
int controlLoopInterval = 100;
void setup()
{
  ET.begin(details(pixydata), &Serial);
  pixy.init();
  Serial.begin(9600);
  Serial.print("Starting...\n");
}

void loop()
{
  int i;
  uint16_t blocks;
  char buf[32];


  //------------------------REAL TIME CONTROL LOOP STARTS HERE ---------------------
  // real time clock control
  i++;
  newLoopTime = millis();
  if (newLoopTime - oldLoopTime >= controlLoopInterval)
  {
    // grab blocks!
    blocks = pixy.getBlocks();
    Serial.print("Time: ");
    Serial.println(millis());
    Serial.print("Blocks? ");
    Serial.println(blocks);
    oldLoopTime = newLoopTime;
    if (blocks)
    {
      xValue = pixy.blocks[0].x;          //give x center of object
      pixydata.angle = map(xValue, 0, 319, -37, 37);
      Serial.print("Angle: ");
      Serial.println(pixydata.angle);
      ET.sendData();
    }
  }
  // ---------------------REAL TIME CONTROL LOOP ENDS HERE -------------------------

}
