const int NUMBEROFPINS = 4;
const int SIGNALPINS[NUMBEROFPINS] = {13, 12, 10, 9};
const int SIGNALTIME[NUMBEROFPINS] = {1000, 500, 300, 100};

unsigned long previousMillis[NUMBEROFPINS];        // will store last time LED was updated
int signalState[NUMBEROFPINS];

void SignalControl_Init() {
  // initialize digital pin 13 as an output.
  for (int i = 0; i < NUMBEROFPINS; i++)
  {
    pinMode(SIGNALPINS[i], OUTPUT);
    signalState[i] = LOW;
    SignalControl_OnOff(i, signalState[i]);
    previousMillis[i] = 0;
  }
}

void SignalControl_OnOff(int signalNumber, int state) {
  digitalWrite(SIGNALPINS[signalNumber], state);
}

void SignalControl_Blink() {
  unsigned long currentMillis = millis();             // current time
  for (int i = 0; i < NUMBEROFPINS; i++)
  {
    if (currentMillis - previousMillis[i] >= SIGNALTIME[i]) {   //time of this specific signal has passed - invert
      previousMillis[i] = currentMillis;
      // if the LED is off turn it on and vice-versa:
      if (signalState[i] == LOW) {
        signalState[i] = HIGH;
      } else {
        signalState[i] = LOW;
      }
      SignalControl_OnOff(i, signalState[i]);
    }
  }
}
