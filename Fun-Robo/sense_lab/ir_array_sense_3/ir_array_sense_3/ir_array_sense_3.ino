//defining arrays for ir sensor iteration
float x_vals[] = {-4.567682, -2.035302, 0, 2.035302, 4.567682}; //cm
float y_vals[] = {0.600964, 2.481072, 2.54, 2.481072, 0.600964}; //cm
float theta_vals[] = {2.37365, 1.97222, 1.5708, 1.16937, 0.767945}; //rads

// dynamic arrays for mapping ir sensor readings
float distances[] = {0,0,0,0,0}; //cm
float map_x_vals[] = {0,0,0,0,0}; //cm
float map_y_vals[] = {0,0,0,0,0}; //cm

//defining pins that all the sensors are on
int ir_pins[] = {A0,A1,A2,A3,A4};

//creating global variables to be used for calculations
float ir_reading; //0 to 1023
float ir_distance; //cm
float distance; //cm
float voltage; //volts

void setup() {
  // begin serial communications
  Serial.begin(9600);
}

void loop() {

  // Iterate through IR sensors
  for (int i=0; i<=4; i++){
    
    // turn each reading into a distance
    ir_reading = analogRead(ir_pins[i]);
    ir_distance = short_reading_to_distance(ir_reading);
    distances[i] = ir_distance;    

    // map those distances into local x,y frame
    map_x_vals[i] = x_vals[i] + distances[i] * cos(theta_vals[i]);
    map_y_vals[i] = y_vals[i] + distances[i] * sin(theta_vals[i]);
  }

  //print out all x values for map
  Serial.print(map_x_vals[0]); Serial.print(":"); 
  Serial.print(map_x_vals[1]); Serial.print(":");
  Serial.print(map_x_vals[2]); Serial.print(":");
  Serial.print(map_x_vals[3]); Serial.print(":");
  Serial.print(map_x_vals[4]); Serial.print(":");

  //print out all y values for map
  Serial.print(map_y_vals[0]); Serial.print(":"); 
  Serial.print(map_y_vals[1]); Serial.print(":");
  Serial.print(map_y_vals[2]); Serial.print(":");
  Serial.print(map_y_vals[3]); Serial.print(":");
  Serial.print(map_y_vals[4]); Serial.println(":");

}

//------------Functions----------------
float mid_reading_to_distance(float reading){
  // This function turns the reading from a mid_range IR sensor into a cm distance
  // WARNING: For anything out of the range 10cm to 70cm, this won't work right
  // INPUT: 
  // float reading - this is the straight analog value read in through arduino from the ir sensor
  // OUTPUT:
  // float distance - this is the distance measured in cm

  // first map from reading to a voltage
  voltage = 5.0*(reading/1023);

  // use math to approximate distance from voltage
  distance = pow( (voltage/15.7212), 1/-0.844358 );
  
  return distance;
  }

float short_reading_to_distance(float reading){
  // This function turns the reading from a short_range IR sensor into a cm distance
  // WARNING: For anything out of the range 3.5cm to 30cm, this won't work right
  // INPUT: 
  // float reading - this is the straight analog value read in through arduino from the ir sensor
  // OUTPUT:
  // float distance - this is the distance measured in cm

  // first map from reading to a voltage
  voltage = 5.0*(reading/1023);

  // use math to approximate distance from voltage
  distance = pow( (voltage/8.97257), 1/-0.857144 );
  
  return distance;
  }
