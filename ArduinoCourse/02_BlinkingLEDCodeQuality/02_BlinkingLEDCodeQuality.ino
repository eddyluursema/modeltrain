const int DELAYTIME = 1000;

void setup() {
  // initialize signal output
  SignalControl_Init();
}

// the loop function runs over and over again forever
void loop() {
  SignalControl_On();   // turn the signal on
  delay(DELAYTIME);     // wait for a second
  SignalControl_Off();  // turn the signal off
  delay(DELAYTIME);     // wait for a second
}
