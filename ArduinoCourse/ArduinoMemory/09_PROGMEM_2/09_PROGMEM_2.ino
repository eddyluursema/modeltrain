const int MAXNUMBEROFPINS = 6;
const int MAXNUMBEROFASPECTS = 10;
const int NUMBEROFCOUNTRIES = 4;

enum country : byte {
  NL, DE, BE, FR
};

enum ledState : byte {  //By default C++ will make type int of this; adding the keyword byte saves memory when declaring an array of this type
  OFF, ON, BLINK     //first OFF, will be 0 written to output port
};

const int aspectsPerCountry [NUMBEROFCOUNTRIES] = { 3, 4, 2, 10}; // each country has a different number of aspects
const int pinsPerCountry [NUMBEROFCOUNTRIES] = { 3, 3, 2, 6}; // each country has a different number of pins controlling lights

const ledState aspectLEDS [NUMBEROFCOUNTRIES][MAXNUMBEROFASPECTS][MAXNUMBEROFPINS] = {  // so based on enum these are now of type byte
  { //NL  in this partial example of one country all empty array cells are explicitly set to NULL by the programmer
    {ON,   OFF,  OFF,  NULL, NULL, NULL},  //HALT
    {OFF,  ON,   OFF,  NULL, NULL, NULL},  //WARN
    {OFF,  OFF,  ON,   NULL, NULL, NULL},  //PASS
    {NULL, NULL, NULL, NULL, NULL, NULL},  //DOES NOT EXIST
    {NULL, NULL, NULL, NULL, NULL, NULL},  //DOES NOT EXIST
    {NULL, NULL, NULL, NULL, NULL, NULL},  //DOES NOT EXIST
    {NULL, NULL, NULL, NULL, NULL, NULL},  //DOES NOT EXIST
    {NULL, NULL, NULL, NULL, NULL, NULL},  //DOES NOT EXIST
    {NULL, NULL, NULL, NULL, NULL, NULL},  //DOES NOT EXIST
    {NULL, NULL, NULL, NULL, NULL, NULL}   //DOES NOT EXIST
  },
  { //DE  in this partial example of one country all empty array cells are implicitly set to NULL by the compiler
    {ON, OFF, OFF},  //HALT
    {OFF, ON, ON},   //WARN
    {OFF, OFF, ON},  //PASS
    {OFF, ON, BLINK} //SLOW
  },
  { //BE
    {ON,   OFF,  NULL},  //HALT
    {OFF,  ON,   NULL},  //PASS
    {NULL, NULL, NULL},  //DOES NOT EXIST
    {NULL, NULL, NULL}   //DOES NOT EXIST
  }
  ,
  { //FR
    ON,  OFF, BLINK, ON,  OFF, BLINK,  //IMAGINARY
    OFF, ON,  BLINK, OFF, ON,  BLINK,  //IMAGINARY
    ON,  ON,  BLINK, ON,  ON,  BLINK,  //IMAGINARY
    OFF, OFF, BLINK, OFF, OFF, BLINK,  //IMAGINARY
    ON,  OFF, BLINK, ON,  OFF, BLINK,  //IMAGINARY
    OFF, ON,  BLINK, OFF, ON,  BLINK,  //IMAGINARY
    ON,  ON,  BLINK, ON,  ON,  BLINK,  //IMAGINARY
    OFF, OFF, BLINK, OFF, OFF, BLINK,  //IMAGINARY
    ON,  ON,  BLINK, ON,  ON,  BLINK,  //IMAGINARY
    OFF, OFF, BLINK, OFF, OFF, BLINK   //IMAGINARY
  }
};

char incomingByte = ""; // for incoming serial data

void setup() {
  Serial.begin(9600);
}

void printCountry(int country) {
  for (int aspect = 0; aspect < aspectsPerCountry[country]; aspect++) {
    for (int pin = 0; pin < pinsPerCountry[country]; pin++) {
      switch (aspectLEDS[country][aspect][pin]) {
        case ON:  Serial.print("On    ");
          break;
        case OFF: Serial.print("Off   ");
          break;
        case BLINK: Serial.print("Blink ");
          break;
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
    } else if (incomingByte == 'F') {
      printCountry(FR);
    }
  }
}
