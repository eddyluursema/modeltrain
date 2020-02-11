const int SIGNALPIN = 13;
const int HIGHTIME = 1;
const int LOWTIME = 19;

void setup() {
  // initialize digital pin  as an output.
  pinMode(SIGNALPIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(SIGNALPIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(HIGHTIME);                 // wait for HIGHTIME msec
  digitalWrite(SIGNALPIN, LOW);    // turn the LED off by making the voltage LOW
  delay(LOWTIME);                  // wait for LOWTIME msec
