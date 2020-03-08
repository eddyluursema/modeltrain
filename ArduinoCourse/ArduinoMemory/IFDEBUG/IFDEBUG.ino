# define DEBUG 1

const int DELAYTIME = 1000;

void setup() {
  // initialize signal output
  SignalControl_Init();
#ifdef DEBUG
  Serial.begin(9600);
#endif

}

// the loop function runs over and over again forever
void loop() {
#ifdef DEBUG
  Serial.println("Switch LED on");
#endif
  SignalControl_On();   // turn the signal on
  delay(DELAYTIME);     // wait for a second
#ifdef DEBUG
  Serial.println("Switch LED off");
#endif
  SignalControl_Off();  // turn the signal off
  delay(DELAYTIME);     // wait for a second
}
