//initializing pins
const int R_in = A0;
const int G_in = A1;
const int B_in = A2;

const int R_out = 11;
const int G_out = 9;
const int B_out = 10;

//initializing variables
float R_Vin = 0;
float G_Vin = 0;
float B_Vin = 0;

float R_prop = 0;
float G_prop = 0;
float B_prop = 0;

float R_pwm = 0;
float G_pwm = 0;
float B_pwm = 0;

//initializing maxes and mins of light intensity
float max_light = 0.8;
float min_light = 0.3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //open a serial port w/ computer

  //setting photoresistor pins as INPUT
  pinMode(R_in,INPUT);
  pinMode(G_in,INPUT);
  pinMode(B_in,INPUT);

  //setting RGB LED pins as OUTPUT
  pinMode(R_out,OUTPUT);
  pinMode(G_out,OUTPUT);
  pinMode(B_out, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Calculating pwm value to output for Red
  float r_val = analogRead(R_in);
  R_prop = r_val/1024;
  if (R_prop > max_light)
    {
      R_prop = max_light;
      }
  else if(R_prop < min_light)
    {
      R_prop = min_light;
      }
  R_pwm = 255*(R_prop - min_light)/(max_light-min_light);

  //Calculating pwm value to output for Green
  float g_val = analogRead(G_in);
  G_prop = (g_val/1024);
  if (G_prop > max_light)
    {
      G_prop = max_light;
      }
  else if(G_prop < min_light)
    {
      G_prop = min_light;
      }
  G_pwm = 255*(G_prop - min_light)/(max_light-min_light);

  //Calculating pwm value to output for Blue
  float b_val = analogRead(B_in);
  B_prop = b_val/1024;
  if (B_prop > max_light)
    {
      B_prop = max_light;
      }
  else if(B_prop < min_light)
    {
      B_prop = min_light;
      }
  B_pwm = 255*(B_prop - min_light)/(max_light-min_light);


  
  analogWrite(R_out,R_pwm);
  analogWrite(G_out,G_pwm);
  analogWrite(B_out,B_pwm);
  //delay(1000);

}
