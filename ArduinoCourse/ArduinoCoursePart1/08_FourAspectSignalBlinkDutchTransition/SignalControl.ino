const int NUMBEROFPINS = 3;
const int SIGNALPINS[NUMBEROFPINS] = {13, 12, 10}; //for RED, YELLOW and GREEN LED
unsigned long previousMillis[NUMBEROFPINS];        // will store last time LED was updated used for blinking
unsigned long previousMillisAspect;

enum state {
  SET, TRANSITION, READY  //if state is SET the aspect will light for a minimum of SETTIME msec; then state becomes READY; aspect will not change until next command
};                        // if state is TRANSITION the aspect will light for a minimum of TRANSITIONTIME msec; then aspect NEXTASPECT will light for a minimum of SETTIME msec; then state becomes READY; aspect will not change until next command


int signalState[NUMBEROFPINS];

const int NUMBEROFASPECTS = 4;
const int BLINKTIME = 500;
const int SETTIME = 600;
const int TRANSITIONTIME = 600;

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
state currentState; // this module being a complete signal showing one aspect at a time can be in one of different states
int currentAspect;

int readyForNextCommand() {      // if currentState is READY the system can accept a new command
  return (currentState == READY) ? (1) : (0);
}

void SignalControl_Init() {
  // initialize digital pin 13 as an output.
  for (int i = 0; i < NUMBEROFPINS; i++)
  {
    pinMode(SIGNALPINS[i], OUTPUT);
  };
  currentState = READY;
}

void SignalControl_ShowAspect(int aspectNumber) { //this function only transforms aspect into which lights are on, off or blinking
  for (int i = 0; i < NUMBEROFPINS; i++) {
    if (aspectLEDS[currentCountry][currentAspect][i] == ON || aspectLEDS[currentCountry][currentAspect][i] == OFF) {
      digitalWrite(SIGNALPINS[i], aspectLEDS[currentCountry][aspectNumber][i]);
    }
  }
}

void SignalControl_SetAspect(int aspectNumber) {
  if ((aspectNumber == HALT) && (currentState == PASS)) { //special situation in NL; from PASS to HALT short time WARN is visible
    currentState = TRANSITION;
    SignalControl_ShowAspect(WARN);
  } else {
    currentState = SET;
    SignalControl_ShowAspect(aspectNumber);
  }
  previousMillisAspect = millis();
  currentAspect = aspectNumber;
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
  };
  if (currentMillis - previousMillisAspect >= TRANSITIONTIME) { //special situation WARN between PASS and HALT time has passed
    if (currentState == TRANSITION) {
      currentState = SET;
      SignalControl_ShowAspect(HALT);   //show HALT for at least SETTIME msec
      previousMillisAspect = millis();
    }
  };
  if (currentMillis - previousMillisAspect >= SETTIME) {
    currentState = READY;  //minimum time of SETTIME msec has passed to show aspect
  }
}
