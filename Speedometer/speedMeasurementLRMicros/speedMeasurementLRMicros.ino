/*
  Simple speed measuring system for model train control using two buttons
	Only suited for detection from L to R
*/
const int modelScale = 160;   //the scale the model train is built in e.g. 1:160. Not a constant; can be changed later on
const int sensorLength = 348; //the distance between the sensors in mm
const int LEFTPIN = 11;
const int RIGHTPIN = 12;
long previousMicros;

void setup() {
  pinMode(LEFTPIN, INPUT_PULLUP);
  pinMode(RIGHTPIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  while (digitalRead(LEFTPIN) != 0) { //simple example wait for left sensor to be activated
  }
  previousMicros = micros();
  while (digitalRead(RIGHTPIN) != 0) { //simple example wait for right sensor to be activated
  }
  long intervalMicross = micros() - previousMicros;
  float speed = calculateSpeed(sensorLength, intervalMicross, modelScale);
  Serial.print("Interval is ");
  Serial.print(intervalMicross);
  Serial.print(" Speed is ");
  Serial.print(speed);
  Serial.println(" km/h");
}
