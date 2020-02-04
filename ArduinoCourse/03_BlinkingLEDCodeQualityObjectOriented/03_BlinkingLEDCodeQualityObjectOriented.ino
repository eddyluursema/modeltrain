#include "SignalControl.h"

const int DELAYTIME = 1000;

SignalControl signalcontrol;  //instatiate class

void setup() {
}

// the loop function runs over and over again forever
void loop() {
  signalcontrol.On();   // turn the signal on
  delay(DELAYTIME);     // wait for a second
  signalcontrol.Off();  // turn the signal off
  delay(DELAYTIME);     // wait for a second
}
