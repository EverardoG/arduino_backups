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

//==========================================================================================================================
// Create and initialize global variables, objects and constants (containers for all data)
//==========================================================================================================================

//==========================================================================================================================
// Startup code to configure robot and pretest all robot functionality (to run once)
// and code to setup robot mission for launch
//==========================================================================================================================
void setup() {
  // Step 1) Put your robot setup code here, to run once;

  // Step 2) Put your robot missions setup code here, to run once;
}

//==========================================================================================================================
// Flight code to run continuously until robot is powered down
//==========================================================================================================================
void loop() {
  // Step 3) Put Operator-Input-to-Robot and Robot-Reports-Back-State code in non-real-time "outer" loop:
  // Put real-time dependant sense-think-act control in the inner loop

  // Step 4) Put your main flight code into "inner" soft-real-time while loop structure below, to run repeatedly,
  // at a known fixed "real-time" periodic interval. This "soft-real-timem" loop timing structure, runs fast
  // flight control code once every controlLoopInterval.

  // real-time-loop begins here

  // SENSE
  // TODO add sensor code here

  // THINK 
  // pick robot behavior based on operator input command typed at console

  // ACT
  //ESTOP = digitalRead(eStopPin); // check ESTOP switch

  // real-time-loop begins here

} // end of "outer void loop()
 //==========================================================================================================================
 // END OF Flight Code
  //==========================================================================================================================
