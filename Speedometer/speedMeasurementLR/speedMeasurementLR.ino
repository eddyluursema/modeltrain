/*
  Example code by Eddy Luursema 2022 Febrary

  Simple speed measuring system for model train control using two buttons
	Only suited for detection from L to R usding polling for the IR sensors
*/
const int modelScale = 160;       //the scale the model train is built in e.g. 1:160. Not a constant; can be changed later on
const float sensorLength = 348.0; //the distance between the sensors in mm
const int LEFTPIN = 11;           //change these according the prototype board
const int RIGHTPIN = 12;
long previousMillis;

void setup() {
  pinMode(LEFTPIN, INPUT_PULLUP);
  pinMode(RIGHTPIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  while (digitalRead(LEFTPIN) != 0) {  //wait for left sensor to be activated
  }
  previousMillis = millis();
  while (digitalRead(RIGHTPIN) != 0) { //wait for right sensor to be activated
  }
  //long intervalMillis = millis() - previousMillis; //this could take some extra calculation time
  long currentMillis = millis();
  long intervalMillis = currentMillis - previousMillis;
  float speed = calculateSpeed(sensorLength, intervalMillis, modelScale);
  Serial.print("Interval is ");
  Serial.print(intervalMillis);
  Serial.print(" Speed is ");
  Serial.print(speed);
  Serial.println(" km/h");
}
