//intializing pins
const int sensorPin = A0;
const int LED1 = 3;
const int LED2 = 4;
const int LED3 = 5;

//initializing calibration variables
int sensorVal = 0;
int sensorMin = 1023;
int sensorMax = 0;
float baselineVolt = 0;
float baselineTemp = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //open a serial port

  // calibrating sensor to get min and max sensor values
  while (millis() < 5000) {
    sensorVal = analogRead(sensorPin);
    
    //record maximum sensor value
    if (sensorVal > sensorMax) {
      sensorMax = sensorVal;
      }
    }
    //record minimum sensor value
    if (sensorVal < sensorMin) {
      sensorMin = sensorVal;
      }

  // calculating baseline temperature using max sensor value
  baselineVolt = (sensorMax/1024.0)*5.0;
  baselineTemp = 100.0*baselineVolt-50.0;
  Serial.print(" The baseline temp is: ");
  Serial.println(baselineTemp);
  Serial.println("");

  // setting LED pins as outputs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  
}



void loop() {
  // put your main code here, to run repeatedly:
  sensorVal = analogRead(sensorPin);
  float voltage = (sensorVal/1024.0)*5.0;
  float temp = 100.0*voltage-50.0;

  Serial.print("Sensor Value: ");
  Serial.println(sensorVal);
  Serial.print("Voltage Measured: ");
  Serial.println(voltage);
  Serial.print("Temparature Measured: ");
  Serial.print(temp);
  Serial.println(" degrees Celcius");
  Serial.println("");
  
  delay(500);

  if ( temp >= baselineTemp + 1 ) {
    digitalWrite(LED1,HIGH);
    if ( temp >= baselineTemp + 2 ){
      digitalWrite(LED2,HIGH);
      if ( temp >= baselineTemp + 3 ){
        digitalWrite(LED3,HIGH);
        }
      }
    }
}
