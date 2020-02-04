const int DELAYTIME = 1000;

void setup() {
  // initialize signal output
  SignalControl_Init();
}

// the loop function runs over and over again forever
void loop() {
  for (int i = 0; i < SignalControl_NumberOfSignals(); i++)
  {
    SignalControl_On(i);   // turn the signal on
    delay(DELAYTIME);     // wait for a second
    SignalControl_Off(i);  // turn the signal off
  }
}
