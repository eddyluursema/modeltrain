# ![Nederlandse vlag](../../images/nl.gif) Nederlands

In deze cursus wordt stapsgewijs gewerkt aan het realiseren van een universele DCC schakeldecoder voor seinen en wissels. De cursus is verder geheel in het Engels.

# ![English flag](../../images/gb.gif)English

In this chapter memory usage and optimalization are discussed. A standard Arduino Uno has only 32k of program and 2k of dynamic memory. We will go to several small programs from the Arduino course to investigate their memory usage and later on we will improve it:

* [Blank program](#Blank_program)
* [Blink](#Blink)
* [Blink with const](Blink_with_const)
* [Blink with separate functions](Blink_with_separate_functions)
* [Four blinking LEDs](Four_blinking_LEDs)
* [Debug compiler directive](Debug_compiler_directive)
* [Multi dimensional arrays](Multi_dimensional_arrays)
* [PROGMEM](PROGMEM)


## Blank_program

A blank program with no contents but setup() and loop() uses 444 bytes of program memory and 9 bytes of dynamic memory (RAM).

```c++
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
```
[TOP](#English)

## Blink

The famous 'Hello world' example, the blinking LED uses 924 bytes program and 9 bytes dynamic memory.

```c++
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
```
[TOP](#English)

## Blink_with_const

Using const is better for maintainability of the program and will cost no extra memory
```c++
const int DELAYTIME = 1000;
const int SIGNALPIN = 13;

void setup() {
  // initialize signal output
  pinMode(SIGNALPIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(SIGNALPIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(DELAYTIME);     // wait for a second
  digitalWrite(SIGNALPIN, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(DELAYTIME);     // wait for a second
}
```

## Blink_with_separate_functions

Even the improved code quality from the Arduino course on this site with separate functions still uses 924 program and 9 bytes dynamic.

```c++
const int SIGNALPIN = 13;

void SignalControl_Init() {
  // initialize digital pin as an output.
  pinMode(SIGNALPIN, OUTPUT);
}

void SignalControl_On() {
  digitalWrite(SIGNALPIN, HIGH);   // turn the LED on (HIGH is the voltage level)
}

void SignalControl_Off() {
  digitalWrite(SIGNALPIN, LOW);   // turn the LED off (LOW is the voltage level)
}
```

```c++
const int DELAYTIME = 1000;

void setup() {
  // initialize signal output
  SignalControl_Init();
}

// the loop function runs over and over again forever
void loop() {
  SignalControl_On();   // turn the signal on
  delay(DELAYTIME);     // wait for a second
  SignalControl_Off();  // turn the signal off
  delay(DELAYTIME);     // wait for a second
}
```

## Four_blinking_LEDs

The four blinking LEDs example uses 962 bytes of program memory.

**First important conclusion: const array is not stored in program memery but in dynamic memory!** Later on in this course is shown how to store a const array in program memory.

Dependig on the array declaration with  **byte** or **int** dynamic memory usage is 13 to 17 bytes because that differs 4 bytes in storage.

**Second important conclusion: if possible declare array elements with the smallest size.**

```c++
const int NUMBEROFPINS = 4;
const int SIGNALPINS[NUMBEROFPINS] = {13, 12, 10, 9};

void SignalControl_Init() {
  // initialize digital pin 13 as an output.
  for (int i = 0; i < NUMBEROFPINS; i++)
  {
    pinMode(SIGNALPINS[i], OUTPUT);
  }
}

int SignalControl_NumberOfSignals(){
  return NUMBEROFPINS;
}

void SignalControl_On(int signalNumber) {
  digitalWrite(SIGNALPINS[signalNumber], HIGH);   // turn the LED on (HIGH is the voltage level)
}

void SignalControl_Off(int signalNumber) {
  digitalWrite(SIGNALPINS[signalNumber], LOW);   // turn the LED off (LOW is the voltage level)
}
```

```c++
const int DELAYTIME = 1000;

void setup() {
  // initialize signal output
  SignalControl_Init();
}

// the loop function runs over and over again forever
void loop() {
  for (int i = 0; i < SignalControl_NumberOfSignals(); i++)
  {
    SignalControl_On(i);   // turn the signal on
    delay(DELAYTIME);     // wait for a second
    SignalControl_Off(i);  // turn the signal off
  }
}
```

## Debug_compiler_directive

If you have debugging code included this can consume a lot of memory. Try using compiler directives. In the following examples (blinking LED with code quality and functions) if debug is switched on 2008 bytes of program and 216 bytes of dynamic memory are used. Switching debug off will give 924 program and 9 dynamic.

```c++
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
```
Switching debug off is simply comment out the directive.

```c++
//# define DEBUG 1
```

## Multi_dimensional_arrays

As programing skills are growing the need for 2- and 3-dimensional arrays will rise. The next example shows a small demo with a 3-D array storing the different signal aspects for several countries where each aspect will have one or more LEDs lightened. Dynamic usage is 307 bytes.

```c++
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
```

What happens if some country has a huge number of lights and aspects? Because the array size is based on the biggest number of ligths and aspects array filling for other countries contain a lot of NULLs. Such an array is called sparse. We have already used a small improvement. The **enum** is defined as **byte**, not as the default int. In one of the sub matrices all NULL values are defined to show the sparse array. Program usage 2068 bytes, dynamic usage is **491** bytes.

```c++
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
```

Dynamic memory can be reduced by a technique for sparse arrays. All information is stored in a one dimensional array with a bit of extra information on each sub matrix per country. The software must handle this extra information to walk through the large array. Program usage is now 1960 bytes and dynamic is **327** bytes.

```c++
enum country : byte {
  NL, DE, BE, FR
};

enum ledState : byte {  //By default C++ will make type int of this; adding the keyword byte saves memory when declaring an array of this type
  OFF, ON, BLINK     //first OFF, will be 0 written to output port
};

// the sparse 3 dimensional array is replaced with one array containing all information; the size is set by defining the elements (C++ feature)
const ledState aspectLEDS [] = {
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
    arrayPointer = arrayPointer + 2 + aspectLEDS[arrayPointer] * aspectLEDS[arrayPointer + 1]; // arrayPointer must point to number of aspects of selected country
  };
  //Serial.print("Start of memory position per country ");
  //Serial.println(arrayPointer);
  for (int aspect = 0; aspect < aspectLEDS[arrayPointer]; aspect++) { // walk through aspects of this country
    for (int pin = 0; pin < aspectLEDS[arrayPointer + 1]; pin++) { // walk through pins of this country
      //Serial.print("Memory position now ");
      //Serial.println(arrayPointer + 2 + aspect * aspectLEDS[arrayPointer + 1] + pin);
      switch (aspectLEDS[arrayPointer + 2 + aspect * aspectLEDS[arrayPointer + 1] + pin]) {
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
```

## PROGMEM

As stated before const array is stored in dynamic, not in program memory. There is a way to store it in program memory using a special keyword. The disadvantage is that retrieving an array element is also it bit more complex. The biggest array aspectLEDS is stored in program memory which now occupies **1960** bytes and **235** bytes dynamic.

```c++
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
```

## Serial_print

If you use a lot of Serial.print("some text") this text is again stored in dynamic memory. Using a special macro F (already defined ). [See link](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/). The code using F occupies now **1994** (34 more) bytes program and **213** (22 less) bytes dynamic memory.

```c++
//#include <avr/pgmspace.h>

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
      switch (pgm_read_byte_near(aspectLEDS + arrayPointer + 2 + aspect * pgm_read_byte_near(aspectLEDS + arrayPointer + 1) + pin)) {
        case ON:  Serial.print(F("On    "));
          break;
        case OFF: Serial.print(F("Off   "));
          break;
        case BLINK: Serial.print(F("Blink "));
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
```
