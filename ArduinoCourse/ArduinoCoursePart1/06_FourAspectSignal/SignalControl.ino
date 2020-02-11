const int NUMBEROFPINS = 3;
const int SIGNALPINS[NUMBEROFPINS] = {13, 12, 10}; //for RED, YELLOW and GREEN LED

const int NUMBEROFASPECTS = 4;
enum ledState {
  OFF, ON     //first OFF, will be 0 written to output port
};

int aspectLEDS [NUMBEROFASPECTS][NUMBEROFPINS] = {
  {ON, OFF, OFF},  //HALT
  {OFF, ON, OFF},  //WARN
  {OFF, OFF, ON},  //PASS
  {ON, OFF, ON}    //SLOW
};

void SignalControl_Init() {
  // initialize digital pin 13 as an output.
  for (int i = 0; i < NUMBEROFPINS; i++)
  {
    pinMode(SIGNALPINS[i], OUTPUT);
  }
}

void SignalControl_ShowAspect(int aspectNumber) {
  Serial.print("Showing aspect: ");
  Serial.println(aspectNumber);
  for (int i = 0; i < NUMBEROFPINS; i++) {
    digitalWrite(SIGNALPINS[i], aspectLEDS[aspectNumber][i]);
  }
}
