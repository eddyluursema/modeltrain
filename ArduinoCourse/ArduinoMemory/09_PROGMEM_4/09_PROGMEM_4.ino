#include <avr/pgmspace.h>

enum country : byte {
  NL, DE, BE, FR
};

enum ledState : byte {  //By default C++ will make type int of this; adding the keyword byte saves memory when declaring an array of this type
  OFF, ON, BLINK     //first OFF, will be 0 written to output port
};

// the sparse 3 dimensional array is replaced with one array containing all information; the size is set by defining the elements (C++ feature)
const PROGMEM ledState aspectLEDS []  = {
  //NL                      is on array position 0; sub matrix is 3 by 3
  3, //number of aspects
  3, //number of pins
  ON,   OFF,  OFF,  //HALT
  OFF,  ON,   OFF,  //WARN
  OFF,  OFF,  ON,  //PASS
  //DE                      is on array position 11; sub matrix is 4 by 3
  4, //number of aspects
  3, //number of pins
  ON, OFF, OFF,  //HALT
  OFF, ON, ON,   //WARN
  OFF, OFF, ON,  //PASS
  OFF, ON, BLINK, //SLOW
  //BE                      is on array position 25; sub matrix is 2 by 2
  2, //number of aspects
  2, //number of pins
  ON,   OFF,  //HALT
  OFF,  ON,   //PASS
  //FR                      is on array position 32; sub matrix is 10 by 6
  10, //number of aspects
  6, //number of pins
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
};

char incomingByte = ""; // for incoming serial data

void setup() {
  Serial.begin(9600);
}

void printCountry(int country) {
  int arrayPointer = 0;
  for (int countrypointer = 0; countrypointer < country; countrypointer++) {
    arrayPointer = arrayPointer + 2 + pgm_read_byte_near(aspectLEDS + arrayPointer) * pgm_read_byte_near(aspectLEDS + arrayPointer + 1); // arrayPointer must point to number of aspects of selected country
  };
  //Serial.print("Start of memory position per country ");
  //Serial.println(arrayPointer);
  for (int aspect = 0; aspect < pgm_read_byte_near(aspectLEDS + arrayPointer); aspect++) { // walk through aspects of this country
    for (int pin = 0; pin < pgm_read_byte_near(aspectLEDS + arrayPointer + 1); pin++) { // walk through pins of this country
      //Serial.print("Memory position now ");
      //Serial.println(arrayPointer + 2 + aspect * aspectLEDS[arrayPointer + 1] + pin);
      switch (pgm_read_byte_near(aspectLEDS + arrayPointer + 2 + aspect * pgm_read_byte_near(aspectLEDS + arrayPointer + 1) + pin)) {
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
