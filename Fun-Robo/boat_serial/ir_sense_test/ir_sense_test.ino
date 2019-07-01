float ir_1_val = 0;
int ir_2_val = 0;
int ir_3_val = 0;
int ir_4_val = 0;
int ir_5_val = 0;

int ir_1_pin = 15; //A1 pin
int ir_2_pin = 16; //A2
int ir_3_pin = 17; //A3
int ir_4_pin = 18; //A4
int ir_5_pin = 19; //A5

int led_1_val = 0;
int led_2_val = 0;
int led_3_val = 0;
int led_4_val = 0;
int led_5_val = 0;

int led_1_pin = 3;
int led_2_pin = 5;
int led_3_pin = 6;
int led_4_pin = 9;
// there is no LED yet

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // set up LED pins as digital output pins
  pinMode(led_1_pin, OUTPUT);
  pinMode(led_2_pin, OUTPUT);
  pinMode(led_3_pin, OUTPUT);
  pinMode(led_4_pin, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  // read in sensor values
  ir_1_val = analogRead(ir_1_pin);
  ir_2_val = analogRead(ir_2_pin);
  ir_3_val = analogRead(ir_3_pin);
  ir_4_val = analogRead(ir_4_pin);
  ir_5_val = analogRead(ir_5_pin);

  float ir_1_v = (ir_1_val*5)/1024;
  Serial.println(ir_1_v);

  // update LEDs accordingly
  analogWrite(led_1_pin, ir_1_val);
  analogWrite(led_2_pin, ir_2_val);
  analogWrite(led_3_pin, ir_3_val);
  analogWrite(led_4_pin, ir_4_val);
  
  }
