enum sigalAspects {
  HALT, WARN, PASS, SLOW
};
void setup() {
  // initialize signal output
  SignalControl_Init();
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  char inputchar = ' ';
  if (Serial.available()) {
    inputchar = Serial.read();
    switch (inputchar) {
      case 'H':
        SignalControl_ShowAspect(HALT);
        break;
      case 'W':
        SignalControl_ShowAspect(WARN);
        break;
      case 'P':
        SignalControl_ShowAspect(PASS);
        break;
      case 'S':
        SignalControl_ShowAspect(SLOW);
        break;
    };
  }
}
