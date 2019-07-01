#include <Servo.h>

// creating Servo objects
Servo panServo;
Servo tiltServo;

// initializing variables
int panPos = 0;
int tiltPos = 0;
int commandPan;
int commandTilt;
String commandLaser;
bool laserOn = false;
const int laserPin = 11;
int laserState = LOW;

float commandX = 5;
float commandY = 5;
float wallDistance = 68;
int sign1;
int sign2;
long one = 1;

// Setting pins
void setup(){
  Serial.begin(9600);
  pinMode(laserPin, OUTPUT);
  panServo.attach(13);
  tiltServo.attach(12);
  }

void loop(){
  // turn on laser
  digitalWrite(laserPin,HIGH);

  if (random(1,3) == 1){
    sign1 = 1;
    }
  else {
    sign1 = -1;
    }
 if (random(1,2) == 1){
    sign2 = 1;
    }
  else {
    sign2 = -1;
    }
    
  // draw a square
  drawSquare(random(10,100), sign1*random(0,50), sign2*random(0,50), wallDistance);
}

//------------------------------------------------FUNCTIONS BELOW ------------------------------------------------------

//OCU functions
int getOperatorInput_x() {
  //This function asks the Operator for an angle for the pan servo and sets that as the tilt servo angle
  Serial.println("==========================================================================================");
  Serial.println("| Hello! Welcome to the laser-turret operator interface! Give me an angle for my pan     |");
  Serial.println("|       servo!                                                                           |");
  Serial.println("==========================================================================================");
  while (Serial.available() == 0) {};                  // do nothing until operator input typed
  commandPan = Serial.readString().toInt();                       // read command string
  Serial.print("| Setting pan servo angle to "); // give command feedback to operator
  Serial.println(commandPan);
  Serial.println(" degrees");
  return commandPan;
}

int getOperatorInput_y(){
  //This function asks the Operator for an angle for the tilt servo and sets that as the tilt servo angle
  Serial.println("==========================================================================================");
  Serial.println("| Now give me an angle for my tilt servo!                                                |");
  Serial.println("|                                                                                        |");
  Serial.println("==========================================================================================");
  while (Serial.available() == 0) {};                  // do nothing until operator input typed
  commandTilt = Serial.readString().toInt();                       // read command string
  Serial.print("| Setting tilt servo angle to "); // give command feedback to operator
  Serial.print(commandTilt);
  Serial.println(" degrees");
  return commandTilt;
}

bool getLaserInput(){
  // This functions prompts the Operator for whether or not to turn on the laser
  Serial.println("==========================================================================================");
  Serial.println("| Hello! Welcome to the laser-turret operator interface! Type on for me to turn on my    |");
  Serial.println("|       laser or off for me to leave it off                                              |");
  Serial.println("==========================================================================================");
  while (Serial.available() == 0) {};                  // do nothing until operator input typed
  commandLaser = Serial.readString();                       // read command string
  Serial.print("| Setting laser to "); 
  Serial.println(commandLaser);// give command feedback to operator
  if (commandLaser == "on"){
    laserOn = true;
    }
  else {
    laserOn = false;
    }
  return laserOn;
  }


// ACT Functions
int determineLaserState(bool laserOn){
  // This function determines whether to turn the laser on/ off
  if (laserOn == true){
    laserState = HIGH;
    }
  else{
    laserState = LOW;
    }
  return laserState;
  }

void posServos(float x,float y, float L) {
  // changes the position of the servos to match x and y inputs
  // float x - x position on wall
  // float y - y position on wall
  // float L - distance from laser to wall
  
  float theta = atan(x/L)*180/3.14 + 112; //pan
  float phi = atan(-y/(sqrt(pow(L,2)+pow(x,2))))*180/3.14 + 103; //tilt
  
  panServo.write(theta);
  tiltServo.write(phi);
  }

void drawLine(float x1, float y1, float x2, float y2, float L){
  // draws a line from x1,y1 to x2,y2
  // float x1 - starting x position
  // float y1 - starting y position
  // float x2 - ending x position
  // float y2 - ending y position
  // float L - distance from laser to wall
  // timeDelay - how quickly in ms to draw the line
  float res = 100; // resolution
  float x_step = (x2-x1)/res;
  float y_step = (y2-y1)/res;

  // interpolate to get from x1,y1 to x2,y2 in a straight line
  int i;
  for (i = 0; i <= res; i++){
    posServos(x1+(x_step)*i,y1+(y_step)*i,L);
    delay(15);
  }
}

void drawSquare(float len, float x0, float y0, float L){
  // draws a square with sides of length len around origin x0, y0
  // float len - length in inches of square sides
  // float x0 - x part of origin
  // float y0 - y part of origin
  // float L - distance from laser turret to wall
  drawLine(x0 - len/2, y0 + len/2, x0 + len/2, y0 + len/2, L);
  drawLine(x0 + len/2, y0 + len/2, x0 + len/2, y0 - len/2, L);
  drawLine(x0 + len/2, y0 - len/2, x0 - len/2, y0 - len/2, L);
  drawLine(x0 - len/2, y0 - len/2, x0 - len/2, y0 + len/2, L);
  }
  
