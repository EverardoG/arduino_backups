int switchState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(2,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  switchState = digitalRead(2);
  
  if (switchState == LOW) {
  // The button has not been pressed 
  
    digitalWrite(3,HIGH); //green LED on
    digitalWrite(5,LOW); // red LED off
    digitalWrite(6,LOW); // red LED off
  }
  
  else { 
  //the button has been pressed
  digitalWrite(3,LOW); //green LED off
  analogWrite(5,0); //red LED off
  analogWrite(6,0); //red LED off
  
  // first red LED dims on
  for (int i = 0;i<= 255;i++)
    {
      analogWrite(5,i);
      delay(20);
    }
  // second red LED dims on
  for (int i = 0;i<= 255;i++)
    {
      analogWrite(6,i);
      delay(20);
    }
 // flash the red LEDs 10 times
  for (int i = 1;i<= 10;i++)
    {
      analogWrite(5,0);
      analogWrite(6,0);
      delay(250);
      analogWrite(5,255);
      analogWrite(6,255);
      delay(250);
    }
    
    }
}
