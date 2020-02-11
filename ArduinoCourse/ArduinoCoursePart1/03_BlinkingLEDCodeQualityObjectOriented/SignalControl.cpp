#include "SignalControl.h"

SignalControl::SignalControl() {
  // initialize digital pin as an output.
  pinMode(SIGNALPIN, OUTPUT);
}

void SignalControl::On() {
  digitalWrite(SIGNALPIN, HIGH);   // turn the LED on (HIGH is the voltage level)
}

void SignalControl::Off() {
  digitalWrite(SIGNALPIN, LOW);   // turn the LED off (LOW is the voltage level)
}
