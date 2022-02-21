/*
  Example code by Eddy Luursema 2022 Febrary
  
  Simple speed measuring system for model train control using two IR gatesways
  This example uses interrupts on pin2 and 3 of the Atmel386P which can be configured for interrupts for a locomotive coming from left of right
*/
const int modelScale = 160;         //the scale the model train is built in e.g. 1:160. Not a constant; can be changed later on using button
const float sensorLength = 348.0;   //the distance between the sensors in mm
const int LEFTPIN = 2;              //must be 2 or 3 on a Arduino Uno/Nano
const int RIGHTPIN = 3;             //must be 2 or 3 on a Arduino Uno/Nano
enum state {NONE, LEFTIN, RIGHTIN}; //is the loc outside the gateway, entered from left or entered from right

volatile state passState; //where is the loc
long previousMillis, currentMillis;
long intervalMillis;
float averageSpeed;
int averageNumber;
volatile bool printState;

void interruptLeft() {
  currentMillis = millis();           //directly after interrupt to assure accurate measurement
  if (passState == NONE) {            //if there would be second interrupt due to bouncing effect of IR gateway, no problem.
    passState = LEFTIN;               //loc is coming from left, save that
    printState = true;
    previousMillis = currentMillis;   //time of entrance is saved
  } else if (passState == RIGHTIN) {  //loc came from right and is now leaving left, start calculation
    intervalMillis = currentMillis - previousMillis;
    passState = NONE;
  }
}

void interruptRight() {
  currentMillis = millis();         //directly after interrupt to assure accurate measurement
  if (passState == NONE) {          //if there would be second interrupt due to bouncing effect of IR gateway, no problem.
    passState = RIGHTIN;           //loc is coming from left, save that
    printState = true;
    previousMillis = currentMillis; //time of entrance is saved
  } else if (passState == LEFTIN) { //loc came from left and is now leaving right, start calculation
    intervalMillis = currentMillis - previousMillis;
    passState = NONE;
  }
}

void setup() {
  pinMode(LEFTPIN, INPUT_PULLUP);
  pinMode(RIGHTPIN, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(LEFTPIN), interruptLeft, FALLING);
  attachInterrupt(digitalPinToInterrupt(RIGHTPIN), interruptRight, FALLING);
  passState = NONE;   //start without locomotive between gateways
  printState = true; //used as semaphore between interrupt routine and main loop. If true print direction
  intervalMillis = 0; //used as semaphore between interrupt routine and main loop. If unequal 0 print interval and speed
  averageSpeed = 0.0;
  averageNumber = 0;
}
void loop() {
  if (printState) {   //semaphore indicates one of the interrupt functions has direction to print
    if (passState == LEFTIN) {
      Serial.println(">>");
    } else {
      Serial.println("<<");
    }
    printState = false;   //so direction is only printed once
  }
  if (intervalMillis != 0) {  //semaphore indicates one of the interrupt functions has interval and speed to print
    float speed = calculateSpeed(sensorLength, intervalMillis, modelScale);
    Serial.print("Interval is ");
    Serial.print(intervalMillis);
    Serial.print(" Speed is ");
    Serial.print(speed);
    Serial.print(" gem. ");
    averageSpeed = averageSpeed + speed;
    averageNumber++;
    float average = averageSpeed / float(averageNumber);
    Serial.print(average);
    Serial.print(" km/h");
    Serial.print(" #");
    Serial.print(averageNumber);
    intervalMillis = 0;   //so interval is only printed once
  }
}
