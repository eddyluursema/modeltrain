# ![Nederlandse vlag](../../images/nl.gif) Nederlands

In deze cursus wordt stapsgewijs gewerkt aan het realiseren van een universele DCC schakeldecoder voor seinen en wissels. De cursus is verder geheel in het Engels.

# ![English flag](../../images/gb.gif)English

In this course a universal DCC decoder for signals and switches is build step by step. This course is to encourage everyone to start loving the Arduino platform to be used in model railroad automation. Part 1 is to control LEDs, control country dependant aspects of signals including blinking. These are the examples (work in progress).

* [Blinking LED](#01_BlinkingLED)
* [Blinking LED code quality](#02_BlinkingLEDcodequality)
* [Blinking LED with code quality and object oriented](#03_BlinkingLEDCodeQualityObjectOriented)
* [Four blinking LEDs](#04_FourBlinkingLEDS)
* [Four blinking LEDs with different frequencies](#05_FourBlinkingLEDSDifferentFrequencyFour)
* [Four aspect signal](#06_FourAspectSignalspectSignal)
* [Four aspect signal with blinking](#07_FourAspectSignalBlink)
* [Four aspect signal with blinking and Dutch transition](08_FourAspectSignalBlinkDutchTransition)



## 01_BlinkingLED

We are using an Arduino Uno with 8 LEDs for most of the examples.

![schematic](./images/Arduino8LED.PNG)

This is the famous example build in every Arduino by default. The LED on pin 13 blinks with a frequency of 1/2 Hz.
Keywords in this example: **void, setup, pinMode, loop, digitalWrite, delay, HIGH, LOW**
```c++
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}
```
[TOP](#English)


## 02_BlinkingLEDcodequality

Keywords in this example: **const**

Most software developers will have two fields of improvement of the previous code

1. Get rid of 'magic' number
2. Split code into functional parts in separate files or tabs


#### No 'magic' numbers

In the code we refer to pin 13 three times. As the code gets bigger changing pin 13 to for example pin 3 is tedious work and one code part is easily forgotten. Thats why a constant is defined (name is written in capitals) and in the code every reference to the pin is done by SIGNALPIN.

#### Split code into functional parts

In this example a second file is created by clicking in the Arduino IDE on New Tab. In that new file with name 'SignalControl' three functions are created to initialize the output port and to switch the LED on and off.

**SignalControl.ino**

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

**02_BlinkingLEDCodeQuality.ino**

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
Suppose the LED is connected to the Arduino with the anode connected to power. Then switching the LED on means writing a LOW to the output port. If a function SignalControl_On was **not** used in every place in the code of the main program the developer must be aware that the LED is connected differently.

If our DCC switch and signal decoder becomes more universal and remotely programmable the fact that the LED is switched on either by putting the output LOW or HIGH depending on some setting, all that intelligence is 'hidden' in the file SignalControl.ino. The developer of the main program only switches a LED on or off. When the electronics of the Arduino is extended with some hardware to enlarge the number of outputs(for example by using an I2C extender like the MCP23070) again the software for controlling that extender is 'hidden' in SignalControl.ino.

[TOP](#English)


## 03_BlinkingLEDCodeQualityObjectOriented

In [this article](https://www.arduino.cc/en/Hacking/libraryTutorial) is explained how our example 02 can be rewritten into an object oriented solution with a header file, an implementation file and a main program. Also a good tutorial can be found [here](https://roboticsbackend.com/arduino-object-oriented-programming-oop/).

Keywords in this example: **class, public, #include, #ifndef, #define, #endif**

**SignalControl.h**

```c++
#ifndef SignalControl_h
#define SignalControl_h

#include "Arduino.h"

const int SIGNALPIN = 13;

class SignalControl
{
  public: SignalControl();
    void On();
    void Off();
};

#endif
```

A class definition (in the .h file) is an abstract of how the class SignalControl behaves to 'users' of this class. The user of the class, the software developer, can create one or more instances of this class. The class has three public functions: On(), Off() and the function, which is called automatically when an instance is created, with the same name as the class name (by convention). Class definitions are put into a header file with extension .h.

**SignalControl.cpp**

```c++
#include "SignalControl.h"

SignalControl::SignalControl() {
  // initialize digital pin as an output.
  pinMode(SIGNALPIN, OUTPUT);
}

void SignalControl::On() {
  digitalWrite(SIGNALPIN, HIGH);   // turn the LED on (HIGH is the voltage level)
}

void SignalControl::Off() {
  digitalWrite(SIGNALPIN, LOW);   // turn the LED off (LOW is the voltage level)
}
```

Knowing the meaning of all the definitions in the header file, this code of the cpp file containing the implementations of the definitions is almost the same as in the previous example.

**03_BlinkingLEDCodeQualityObjectOriented.ino**
```c++
#include "SignalControl.h"

const int DELAYTIME = 1000;

SignalControl signalcontrol;  //instantiate class; implicit call of initialization function

void setup() {
}

// the loop function runs over and over again forever
void loop() {
  signalcontrol.On();   // turn the signal on
  delay(DELAYTIME);     // wait for a second
  signalcontrol.Off();  // turn the signal off
  delay(DELAYTIME);     // wait for a second
}
```

In definition we use <class name>::<function name>; when called <class name>.<function name>

**In the examples below we will use conventional Arduino programming without classes. All files will have extension .ino**

[TOP](#English)


## 04_FourBlinkingLEDS

The example is extended to blink 4 LEDs in turn.
Keywords in this example: **[** and **]** for arrays

**SignalControl.ino**

```c++
const int NUMBEROFPINS = 4;
const int SIGNALPINS[NUMBEROFPINS] = {13, 12, 11, 10};

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

**04_BlinkingLEDCodeQuality.ino**
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
SignalControl.ino now has an array with pin numbers. The numbers of pins is a constant and is defined **before** the array gets its size. The initialization sets all output ports. The ON and OFF functions get a parameter to indicate which logical LED number 0..3 must be switched on or off. The programmer of the main program has no knowledge of the physical pin numbers. The only problem is that he also has no knowledge of the number of signals (later in the course will talk about the number of signal aspects to that's why we switch to 'number of signals').A function is created which returns the number of signals so in the main program we refer to that function. Changing the number of LEDs is done in **one** place. The file containing code to control a certain set of hardware is often called a 'library'.

[TOP](#English)


## 05_FourBlinkingLEDSDifferentFrequencyFour

In the previous example we created a sort of 'Knight Rider' (old television series with an intelligent car having a set of LEDs at the front). Now the task is to let each LED blink at different frequencies. To solve this we must get rid of the delay().

Keywords in this example: **unsigned long, millis()**

**SignalControl.ino**
```c++
const int NUMBEROFPINS = 4;
const int SIGNALPINS[NUMBEROFPINS] = {13, 12, 11, 10};
const int SIGNALTIME[NUMBEROFPINS] = {1000, 500, 300, 100};

unsigned long previousMillis[NUMBEROFPINS];        // will store last time LED was updated
int signalState[NUMBEROFPINS];

void SignalControl_Init() {
  // initialize digital pin 13 as an output.
  for (int i = 0; i < NUMBEROFPINS; i++)
  {
    pinMode(SIGNALPINS[i], OUTPUT);
    signalState[i] = LOW;
    SignalControl_OnOff(i, signalState[i]);
    previousMillis[i] = 0;
  }
}

void SignalControl_OnOff(int signalNumber, int state) {
  digitalWrite(SIGNALPINS[signalNumber], state);
}

void SignalControl_Blink() {
  unsigned long currentMillis = millis();             // current time
  for (int i = 0; i < NUMBEROFPINS; i++)
  {
    if (currentMillis - previousMillis[i] >= SIGNALTIME[i]) {   //time of this specific signal has passed - invert
      previousMillis[i] = currentMillis;
      // if the LED is off turn it on and vice-versa:
      if (signalState[i] == LOW) {
        signalState[i] = HIGH;
      } else {
        signalState[i] = LOW;
      }
      SignalControl_OnOff(i, signalState[i]);
    }
  }
}
```
**05_FourBlinkingLEDSDifferentFrequency.ino**

```c++
void setup() {
  // initialize signal output
  SignalControl_Init();
}

// the loop function runs over and over again forever
void loop() {
  SignalControl_Blink();
}
```
The blinking software is now completely transferred into the library. The state of each signal is remembered in array ledState and the last time we flipped that signal is stored in array previousMillis. In the initalization the state is set to LOW and the signal/LED is turned off. In the previous code examples we assumed that setting an output of the Arduino implicitly sets the output LOW. Not assuming but setting it yourself is better. The same is for the array previousMillis: set it to 0 in the initialization function.

[TOP](#English)


## 06_FourAspectSignalspectSignal

In the real world of model trains were are not switching individual LEDs on and off but rather switch a combination of one or more LEDs on, off or blinking. A signal is set to a specific aspect. In SignalControl.ino a 2D- array is specified containing the transformation of aspect to one ore more burning LEDs. In this example a keyboard key is send to the Arduino through the Arduine IDE monitor and the Arduino will light up the aspect HALT, WARN, PASS or SLOW (just imaginary aspects with imaginary light settings). The Arduino IDE is not capable of sending separate characters; you have to push Enter to send the entered key(s) in the monitor to the Arduino.

Keywords in this example: **enum, Serial.begin, Serial.print, Serial.available, Serial.read**

**SignalControl.ino**

```c++
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
```

**06_FourAspectSignal.ino**

```c++
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
```

[TOP](#English)


## 07_FourAspectSignalBlink

The previous example can easily be extended to a version with a third state of a LED: blinking. Again a software timer is used (not a delay). An extra feature of this example is the possibility to have different lights for each aspect depending on the user selected country.

**SignalControl.ino**

```c++
const int NUMBEROFPINS = 3;
const int SIGNALPINS[NUMBEROFPINS] = {13, 12, 10}; //for RED, YELLOW and GREEN LED
unsigned long previousMillis[NUMBEROFPINS];        // will store last time LED was updated
int signalState[NUMBEROFPINS];

const int NUMBEROFASPECTS = 4;
const int BLINKTIME = 500;
enum ledState {
  OFF, ON, BLINK     //first OFF, will be 0 written to output port
};

int aspectLEDS [NUMBEROFCOUNTRIES][NUMBEROFASPECTS][NUMBEROFPINS] = {
  { //NL
    {ON, OFF, OFF},  //HALT
    {OFF, ON, OFF},  //WARN
    {OFF, OFF, ON},  //PASS
    {OFF, ON, BLINK} //SLOW does not exist in NL
  },
  { //DE
    {ON, OFF, OFF},  //HALT
    {OFF, ON, ON},   //WARN
    {OFF, OFF, ON},  //PASS
    {OFF, ON, BLINK} //SLOW does not exist in DE
  }
};
int currentAspect;

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
  currentAspect = aspectNumber;
  for (int i = 0; i < NUMBEROFPINS; i++) {
    if (aspectLEDS[currentCountry][currentAspect][i] == ON || aspectLEDS[currentCountry][currentAspect][i] == OFF) {
      digitalWrite(SIGNALPINS[i], aspectLEDS[currentCountry][aspectNumber][i]);
    }
  }
}

void SignalControl_Blink() {
  unsigned long currentMillis = millis();             // current time
  for (int i = 0; i < NUMBEROFPINS; i++)
  {
    if ((aspectLEDS[currentCountry][currentAspect][i] == BLINK) && (currentMillis - previousMillis[i] >= BLINKTIME)) {   //time of this specific signal has passed - invert
      previousMillis[i] = currentMillis;
      // if the LED is off turn it on and vice-versa:
      if (signalState[i] == LOW) {
        signalState[i] = HIGH;
      } else {
        signalState[i] = LOW;
      }
      digitalWrite(SIGNALPINS[i], signalState[i]);
    }
  }
}
```
**07_FourAspectSignalBlink.ino**
```c++
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
```

## 08_FourAspectSignalBlinkDutchTransition

In the Netherlands there is special situation when a light transits from passing (GREEN light) to no passing (RED light). For a short period of about 0.5 s the YELLOW light appears. In the code below the previous code was extended to show this behaviour. A second propery was added; if multiple commands follow in a short period each aspect is visible for at least 0.6 s.

**SignalControl.ino**
```c++
const int NUMBEROFPINS = 3;
const int SIGNALPINS[NUMBEROFPINS] = {13, 12, 10}; //for RED, YELLOW and GREEN LED
unsigned long previousMillis[NUMBEROFPINS];        // will store last time LED was updated used for blinking
unsigned long previousMillisAspect;

enum state {
  SET, TRANSITION, READY  //if state is SET the aspect will light for a minimum of SETTIME msec; then state becomes READY; aspect will not change until next command
};                        // if state is TRANSITION the aspect will light for a minimum of TRANSITIONTIME msec; then aspect NEXTASPECT will light for a minimum of SETTIME msec; then state becomes READY; aspect will not change until next command


int signalState[NUMBEROFPINS];

const int NUMBEROFASPECTS = 4;
const int BLINKTIME = 500;
const int SETTIME = 600;
const int TRANSITIONTIME = 600;

enum ledState {
  OFF, ON, BLINK     //first OFF, will be 0 written to output port
};

int aspectLEDS [NUMBEROFCOUNTRIES][NUMBEROFASPECTS][NUMBEROFPINS] = {
  { //NL
    {ON, OFF, OFF},  //HALT
    {OFF, ON, OFF},  //WARN
    {OFF, OFF, ON},  //PASS
    {OFF, ON, BLINK} //SLOW does not exist in NL
  },
  { //DE
    {ON, OFF, OFF},  //HALT
    {OFF, ON, ON},   //WARN
    {OFF, OFF, ON},  //PASS
    {OFF, ON, BLINK} //SLOW does not exist in DE
  }
};
state currentState; // this module being a complete signal showing one aspect at a time can be in one of different states
int currentAspect;

int readyForNextCommand() {      // if currentState is READY the system can accept a new command
  return (currentState == READY) ? (1) : (0);
}

void SignalControl_Init() {
  // initialize digital pin 13 as an output.
  for (int i = 0; i < NUMBEROFPINS; i++)
  {
    pinMode(SIGNALPINS[i], OUTPUT);
  };
  currentState = READY;
}

void SignalControl_ShowAspect(int aspectNumber) {
  for (int i = 0; i < NUMBEROFPINS; i++) {
    if (aspectLEDS[currentCountry][currentAspect][i] == ON || aspectLEDS[currentCountry][currentAspect][i] == OFF) {
      digitalWrite(SIGNALPINS[i], aspectLEDS[currentCountry][aspectNumber][i]);
    }
  }
}

void SignalControl_SetAspect(int aspectNumber) {
  if ((aspectNumber == HALT) && (currentState == PASS)) {
    currentState = TRANSITION;
    SignalControl_ShowAspect(WARN);
  } else {
    currentState = SET;
    SignalControl_ShowAspect(aspectNumber);
  }
  previousMillisAspect = millis();
  currentAspect = aspectNumber;
}

void SignalControl_Blink() {
  unsigned long currentMillis = millis();             // current time
  for (int i = 0; i < NUMBEROFPINS; i++)
  {
    if ((aspectLEDS[currentCountry][currentAspect][i] == BLINK) && (currentMillis - previousMillis[i] >= BLINKTIME)) {   //time of this specific signal has passed - invert
      previousMillis[i] = currentMillis;
      // if the LED is off turn it on and vice-versa:
      if (signalState[i] == LOW) {
        signalState[i] = HIGH;
      } else {
        signalState[i] = LOW;
      }
      digitalWrite(SIGNALPINS[i], signalState[i]);
    }
  };
  if (currentMillis - previousMillisAspect >= TRANSITIONTIME) {
    if (currentState == TRANSITION) {
      currentState = SET;
      SignalControl_ShowAspect(HALT);
      previousMillisAspect = millis();
    }
  };
  if (currentMillis - previousMillisAspect >= SETTIME) {
    currentState = READY;
  }
}

```
**08_FourAspectSignalBlinkDutchTransition.ino**
```c++
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
```

[TOP](#English)
