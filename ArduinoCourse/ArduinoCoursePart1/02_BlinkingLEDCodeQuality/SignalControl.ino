const int SIGNALPIN = 13;

void SignalControl_Init() {
  // initialize digital pin as an output.
  pinMode(SIGNALPIN, OUTPUT);
}

void SignalControl_On() {
  digitalWrite(SIGNALPIN, HIGH);   // turn the LED on (HIGH is the voltage level)
}

void SignalControl_Off() {
  digitalWrite(SIGNALPIN, LOW);   // turn the LED off (LOW is the voltage level)
}
