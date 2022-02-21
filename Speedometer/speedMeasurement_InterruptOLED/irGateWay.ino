/*
  All the setup and functions needed to use the two interrupt pins to detect the passing of the IR gateway
*/
const int LEFTPIN = 2;              //interrupt capable pin must be 2 or 3 on a Arduino Uno/Nano
const int RIGHTPIN = 3;             //interrupt capable pin must be 2 or 3 on a Arduino Uno/Nano

void setupIRGateWay () {
  pinMode(LEFTPIN, INPUT_PULLUP);
  pinMode(RIGHTPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LEFTPIN), interruptLeft, FALLING);    //IR gateway goes to LOW when IR is blocked
  attachInterrupt(digitalPinToInterrupt(RIGHTPIN), interruptRight, FALLING);
}
void interruptLeft() {
  currentMillis = millis();          //directly after interrupt to assure accurate measurement
  if (passState == NONE) {           //if there would be second interrupt due to bouncing effect of IR gateway, no problem.
    passState = LEFTIN;              //loc is coming from left, save that
    printDirection = true;           //signal main program loop to print direction only once
    previousMillis = currentMillis;  //time of entrance is saved
  } else if (passState == RIGHTIN) { //loc came from right and is now leaving left, start calculation
    intervalMillis = currentMillis - previousMillis;  //intervalmillis <> 0 means main program loop must print it
    passState = NONE;
  }
}

void interruptRight() {
  currentMillis = millis();         //directly after interrupt to assure accurate measurement
  if (passState == NONE) {          //if there would be second interrupt due to bouncing effect of IR gateway, no problem.
    passState = RIGHTIN;            //loc is coming from left, save that
    printDirection = true;          //signal main program loop to print direction only once
    previousMillis = currentMillis; //time of entrance is saved
  } else if (passState == LEFTIN) { //loc came from left and is now leaving right, start calculation
    intervalMillis = currentMillis - previousMillis;  //intervalmillis <> 0 means main program loop must print it
    passState = NONE;
  }
}
