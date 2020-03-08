const int NUMBEROFPINS = 3;
const int NUMBEROFASPECTS = 4;
const int NUMBEROFCOUNTRIES = 3;

enum country {
  NL, DE, BE     //first OFF, will be 0 written to output port
};

enum ledState {
  OFF, ON, BLINK     //first OFF, will be 0 written to output port
};

const ledState aspectLEDS [NUMBEROFCOUNTRIES][NUMBEROFASPECTS][NUMBEROFPINS] = {
  { //NL
    {ON, OFF, OFF},  //HALT
    {OFF, ON, OFF},  //WARN
    {OFF, OFF, ON},  //PASS
    {OFF, ON, BLINK} //SLOW
  },
  { //DE
    {ON, OFF, OFF},  //HALT
    {OFF, ON, ON},   //WARN
    {OFF, OFF, ON},  //PASS
    {OFF, ON, BLINK} //SLOW
  },
  { //BE
    {ON, OFF, OFF},  //HALT
    {OFF, ON, ON},   //WARN
    {OFF, OFF, ON},  //PASS
    {OFF, BLINK, BLINK} //imaginary data
  }
};

char incomingByte = ""; // for incoming serial data

void setup() {
  Serial.begin(9600);
}

void printCountry(int country) {
  for (int aspect = 0; aspect < NUMBEROFASPECTS; aspect++) {
    for (int pin = 0; pin < NUMBEROFPINS; pin++) {
      if (aspectLEDS[country][aspect][pin] == NL) { // enum can not be printed as string; conversion by code
        Serial.print("On    ");
      }
      else if (aspectLEDS[country][aspect][pin] == DE) {
        Serial.print("Off   ");
      }
      else if (aspectLEDS[country][aspect][pin] == BE) {
        Serial.print("Blink ");
      }
    }
    Serial.println();
  }
}
void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    if ((incomingByte == 'N') || (incomingByte == 'D') || (incomingByte == 'B')) {
      Serial.print("Led states for country: ");
    }
    Serial.println(incomingByte);
    if (incomingByte == 'N') {
      printCountry(NL);
    } else if (incomingByte == 'D') {
      printCountry(DE);
    } else if (incomingByte == 'B') {
      printCountry(BE);
    }
  }

}
