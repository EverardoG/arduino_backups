int pin1 = 10;
int pin2 = 9;
int val1 = 200;
int val2 = 200;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(pin1, val1);
  analogWrite(pin2, val2);
}
