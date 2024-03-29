//initializing pins
const int LED_pin = 12;


void setup() {
  // setup LED pin to digital output and photoresistor to analog input
  pinMode(LED_pin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_pin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
