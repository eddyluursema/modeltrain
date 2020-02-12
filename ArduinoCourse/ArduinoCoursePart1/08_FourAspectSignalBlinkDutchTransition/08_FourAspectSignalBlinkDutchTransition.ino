const int NUMBEROFCOUNTRIES = 2;
enum countries {
  NL, DE
};

enum sigalAspects {
  HALT, WARN, PASS, SLOW
};

countries currentCountry = NL;

void setup() {
  // initialize signal output
  SignalControl_Init();
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  char inputchar = ' ';
  if (Serial.available() && readyForNextCommand()) {
    inputchar = Serial.read();
    switch (inputchar) {
      case 'H':
        SignalControl_SetAspect(HALT);
        break;
      case 'W':
        SignalControl_SetAspect(WARN);
        break;
      case 'P':
        SignalControl_SetAspect(PASS);
        break;
      case 'S':
        SignalControl_SetAspect(SLOW);
        break;
      case '1':
        currentCountry = NL;;
        break;
      case '2':
        currentCountry = DE;;
        break;
    };
  }
  SignalControl_Blink();
}
