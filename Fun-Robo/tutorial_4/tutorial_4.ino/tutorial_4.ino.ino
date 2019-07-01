/****************************************************************************************************************************
   Step 0) Add a clear descriptive title block at the top of your robot code
   Example Title block follows:
   Title: 2018 Fun-Robo Simple Arduino Robot Controller (ENGR 3390 Tutorial 4)
   Description: This structure temlate contains a SENSE-THINK-ACT data flow to allow a Robot to perform a sequence of meta-behaviors in soft-real-tie based on direct
   text commands from a human operator.
   Robot Name?: ***add name here*** Example; TutorialBot 1
   What does code do? ****give a short description of what code does**** Example: poll operator,
   carry out operator text input, loop indefinitely
   Hardware warnings: Turn e-stop motor power on AFTER starting this code
   Created by D.Barret June 2018
 * **************************************************************************************************************************
*/

// TODO: Add directions for future work on code here in this section
// Example: TODO: add sensors to sense section, add motors to act section

//==========================================================================================================================
// Load supporting Arduino Libraries
//==========================================================================================================================
#include <Servo.h> //example of loading ServoMotors library

//==========================================================================================================================
// Create and initialize global variables, objects and constants (containers for all data)
//==========================================================================================================================
const int aliveLED = 13;          // create a name for "robot alive" blinky light pin
const int eStopPin = 12;          // create a name for pin connected to ESTOP switch
boolean aliveLEDState = true;     // create a name for alive blinky light state to be sued with timer
boolean ESTOP = true;             // create a name for Emergency stop of all motors
boolean realTimeRunStop = true;   // create a name for real time control loop flag
String command = "stop    ";      // create a String object name for operator command string
String loopError = "no error";    // create a String for the real time control loop error system
unsigned long oldLoopTime = 0;    // create a name for past loop time in milliseconds
unsigned long newLoopTime = 0;    // create a name for new loop time in milliseconds
unsigned long cycleTime = 0;      // create a name for elapsed loop cycle time
const long controlLoopInterval = 1000; // create a name for control loop cycle time in milliseconds


//==========================================================================================================================
// Startup code to configure robot and pretest all robot functionality (to run once)
// and code to setup robot mission for launch
//==========================================================================================================================
void setup() {
  // Step 1) Put your robot setup code here, to run once;
  pinMode(aliveLED, OUTPUT);        // initialize aliveLED pin as an output
  pinMode(eStopPin, INPUT_PULLUP);  // use internal pull-up on ESTOP switch input pin, this pin is connected to switch connected to ground
  Serial.begin(9600);               // start serial communications at 9600 baud
  Serial.println("Robot Controller Starting Up! Watch your fingers!");

  // Step 2) Put your robot missions setup code here, to run once;
}

//==========================================================================================================================
// Flight code to run continuously until robot is powered down
//==========================================================================================================================
void loop() {
  // Step 3) Put Operator-Input-to-Robot and Robot-Reports-Back-State code in non-real-time "outer" loop:
  // Put real-time dependant sense-think-act control in the inner loop -> this stuff is not real time dependent, you give it a command and it do

  // GET Operater Control Unit (OCU) Input:
  command = getOperatorInput();                         // get operator input from serial monitor
  if (command == "stop") realTimeRunStop = false;       // skip real time inner loop
  else realTimeRunStop = true;                          // Set loop flag to run = true

  // Step 4) Put your main flight code into "inner" soft-real-time while loop structure below, to run repeatedly,
  // at a known fixed "real-time" periodic interval. This "soft-real-time" loop timing structure, runs fast
  // flight control code once every controlLoopInterval.


  //real time loop starts now
  while (realTimeRunStop == true) {                    // if OCU-Stop not commanded, run control loop

    // Check if operator inputs a command during real-time loop execution
    if (Serial.available() > 0) {                     // check to see if operator typed at OCU
      realTimeRunStop = false;                        //if OCU input typed, stop control loop
      command = Serial.readString();                  // read command string to clear buffer
      break;                                          // break out of real time loop
    }
    else {
      realTimeRunStop = true; // if no operator input, run real time loop
    }

    // Real-Time clock control. Check to see if one clock cycle has elapsed before running this control code
    newLoopTime = millis();                                             // get current Arduino time (50 days till wrap)
    if (newLoopTime - oldLoopTime >= controlLoopInterval) {             // if true run flight code
      oldLoopTime = newLoopTime;                                        // reset time stamp
      blinkAliveLED();                                                  // toggle blinky alive light

      // SENSE
      // TODO add sensor code here

      // THINK
      // pick robot behavior based on operator input command typed at console
      if ( command == "stop" ) {
        Serial.println("Stop Robot");
        realTimeRunStop = false;      // exit real time control loop
        break;
      }
      else if (command == "move") {  // Move robot to Operator commanded position
        Serial.println("Move robot ");
        Serial.println("Type stop to stop robot");
        realTimeRunStop = true;      // don't exit loop after running once
      }
      else if (command == "idle") {  // Make robot alive with small motions
        Serial.println("Idle Robot");
        Serial.println("Type stop to stop robot");
        realTimeRunStop = true;      // run loop continually
      }
      else
      {
        Serial.println("******* WARNING ******** Invalid Input, Robot Stopped, Please try again!");
        realTimeRunStop = false;
      }

      // ACT
      ESTOP = digitalRead(eStopPin);                  // check ESTOP

      // Check to see if all code ran successfully in one real-time increment
      cycleTime = millis() - newLoopTime;               // calculate loop execution time
      if ( cycleTime > controlLoopInterval) {
        Serial.println("****************************************");
        Serial.println("error - real time has failed, stop robot!");  // loop took too long to run
        Serial.print("100 ms real-time loop took = ");
        Serial.println(cycleTime);                                    // print loop time
        Serial.println("****************************************");
        break;                                                        // break out of real-time inner loop
      }

    } // end of "if (newLoopTime - oldLoopTime >= controlLoopInterval)" real-time loop structure
  } // end of "inner" "while(realTimeRunStop == true)"

  // SEND Robot State to Operator Control Unit(OCU)
  Serial.println("==========================================================================================");
  Serial.println("| Robot control loop stopping to wait for new command ");         // send robot status to operator
  if (ESTOP == true) Serial.println("| Robot motors E-Stopped by external switch");  // send E-Stop message to OCU

  // real-time-loop ends here

} // end of "outer void loop()
//==========================================================================================================================
// END OF Flight Code
//==========================================================================================================================

// OCU Functions
String getOperatorInput() {
  //This funtion prints operator command options on the serial console and prompts
  // operator to input desired robot command
  Serial.println("==========================================================================================");
  Serial.println("| Robot Behavior-Commands: move (moves robot), stop (e-stops motors), idle (robot idles) |");
  Serial.println("|                                                                                        |");
  Serial.println("|     Please type desired robot behavior in command line at the top of this window       |");
  Serial.println("|     and then press SEND button.                                                        |");
  Serial.println("==========================================================================================");
  while (Serial.available() == 0) {};                  // do nothing until operator input typed
  command = Serial.readString();                       // read command string
  Serial.print("| New robot behavior command is:   "); // give command feedback to operator
  Serial.println(command);
  Serial.println("| Type 'stop' to stop control loop and wait for new command                              |");
  Serial.println("==========================================================================================");
  return command;
}

// Realtime loop functions

void blinkAliveLED() {
  // This function toggle state of aliveLED blinky light LED
  // if the LED is off turn it on and vice-versa:
  if (aliveLEDState = LOW) {
    aliveLEDState = HIGH;
  }
  else {
    aliveLEDState = LOW;
  }
  // set the LED with the ledState of the variable:
  digitalWrite(aliveLED, aliveLEDState);
}
