const int UP = 1;
const int DOWN = -1;

int ledState;       // is LED dimming of getting brighter
int ledBrightness;  // will store brightness as the PWM width value between 0 and PWMTIME
int ledDimOrBright; // should led get brighter +1 of must it dimm -1

void setup() {
  // initialize signal output
  SignalControl_Init();
  ledBrightness = 1;
  ledDimOrBright = UP;
}

// the loop function runs over and over again forever
void loop() {
  SignalControl_Blink();
}
