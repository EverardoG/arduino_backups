int const sensorPin = A5;
int sensorVar = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  sensorVar = analogRead(sensorPin);
  Serial.println(sensorVar);
  delay(100);
}
