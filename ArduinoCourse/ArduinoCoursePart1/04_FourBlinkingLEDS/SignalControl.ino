const int NUMBEROFPINS = 4;
const int SIGNALPINS[NUMBEROFPINS] = {13, 12, 10, 9};

void SignalControl_Init() {
  // initialize digital pin 13 as an output.
  for (int i = 0; i < NUMBEROFPINS; i++)
  {
    pinMode(SIGNALPINS[i], OUTPUT);
  }
}

int SignalControl_NumberOfSignals(){
  return NUMBEROFPINS;
}

void SignalControl_On(int signalNumber) {
  digitalWrite(SIGNALPINS[signalNumber], HIGH);   // turn the LED on (HIGH is the voltage level)
}

void SignalControl_Off(int signalNumber) {
  digitalWrite(SIGNALPINS[signalNumber], LOW);   // turn the LED off (LOW is the voltage level)
}
