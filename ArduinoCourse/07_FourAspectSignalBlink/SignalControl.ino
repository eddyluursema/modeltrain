const int NUMBEROFPINS = 3;
const int SIGNALPINS[NUMBEROFPINS] = {13, 12, 10}; //for RED, YELLOW and GREEN LED
unsigned long previousMillis[NUMBEROFPINS];        // will store last time LED was updated
int signalState[NUMBEROFPINS];

const int NUMBEROFASPECTS = 4;
const int BLINKTIME = 500;
enum ledState {
  OFF, ON, BLINK     //first OFF, will be 0 written to output port
};

int aspectLEDS [NUMBEROFCOUNTRIES][NUMBEROFASPECTS][NUMBEROFPINS] = {
  { //NL
    {ON, OFF, OFF},  //HALT
    {OFF, ON, OFF},  //WARN
    {OFF, OFF, ON},  //PASS
    {OFF, ON, BLINK} //SLOW does not exist in NL
  },
  { //DE
    {ON, OFF, OFF},  //HALT
    {OFF, ON, ON},   //WARN
    {OFF, OFF, ON},  //PASS
    {OFF, ON, BLINK} //SLOW does not exist in DE
  }
};
int currentAspect;

void SignalControl_Init() {
  // initialize digital pin 13 as an output.
  for (int i = 0; i < NUMBEROFPINS; i++)
  {
    pinMode(SIGNALPINS[i], OUTPUT);
  }
}

void SignalControl_ShowAspect(int aspectNumber) {
  Serial.print("Showing aspect: ");
  Serial.println(aspectNumber);
  currentAspect = aspectNumber;
  for (int i = 0; i < NUMBEROFPINS; i++) {
    if (aspectLEDS[currentCountry][currentAspect][i] == ON || aspectLEDS[currentCountry][currentAspect][i] == OFF) {
      digitalWrite(SIGNALPINS[i], aspectLEDS[currentCountry][aspectNumber][i]);
    }
  }
}

void SignalControl_Blink() {
  unsigned long currentMillis = millis();             // current time
  for (int i = 0; i < NUMBEROFPINS; i++)
  {
    if ((aspectLEDS[currentCountry][currentAspect][i] == BLINK) && (currentMillis - previousMillis[i] >= BLINKTIME)) {   //time of this specific signal has passed - invert
      previousMillis[i] = currentMillis;
      // if the LED is off turn it on and vice-versa:
      if (signalState[i] == LOW) {
        signalState[i] = HIGH;
      } else {
        signalState[i] = LOW;
      }
      digitalWrite(SIGNALPINS[i], signalState[i]);
    }
  }
}
