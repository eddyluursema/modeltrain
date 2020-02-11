
In this course a universal DCC decoder for signals and switches is build step by step. This course is to encourage everyone to start loving the Arduino platform to be used in model railroad automation. This is part 2 of the course containing examples of LED fading. These are the examples (work in progress):

* [Brightness simple starting example](#09_BrightnessStart)
* [Brightness without delay function](#10_BrightnessWithoutDelay)
* [Brightness without delay 4 LEDs](#11_BrightnessWithoutDelay4LEDs)
* [Fading without delay](#12_FadingWithoutDelay)
* [Fading without delay 4 LEDs and different fading starts](#13_FadingWithoutDelay4LEDs)
* Fading using hardware PWM output: UNDER CONSTRUCTION (14)
* Fading without delay 4 LEDs and blinking: UNDER CONSTRUCTION (15)
* Four aspect signal with fading: UNDER CONSTRUCTION (16)
* Switch control: UNDER CONSTRUCTION (17)


## 09_BrightnessStart

Fading is a lot more complex. In these cases it is wise to start with a smaller example instead of trying to extend the previous example.

Dimming a LED is done through pulse width modulation. At a speed invisible for the human eye the LED is switched on during a certain period and off. The ratio on-off will give the impression that the LED is dimmed.

This example has one LED. Experiment with the values of HIGHTIME and LOWTIME. The sum of HIGHTIME and LOWTIME is the PWM cycle period. In the example this is 20 msec so the LED will flicker at 50 Hz. Lower frequencies are irritating to the eye. Setting the brightness to 1 msec on and 19 msec off is still visible. Flickering at 50 Hz can be made visible in two ways: turn your head fast while lokking at the LED and using the camera of a mobile phone.

**09_BrightnessStart.ino**

```c++
const int SIGNALPIN = 13;
const int HIGHTIME = 1;
const int LOWTIME = 19;

void setup() {
  // initialize digital pin  as an output.
  pinMode(SIGNALPIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(SIGNALPIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(HIGHTIME);                 // wait for HIGHTIME msec
  digitalWrite(SIGNALPIN, LOW);    // turn the LED off by making the voltage LOW
  delay(LOWTIME);                  // wait for LOWTIME msec
}
```

[TOP](#English)


## 10_BrightnessWithoutDelay

Now we rewrite the example above to get rid of the delay function. The smallest time division is one step in the PWM cycle. The LED is switched on at the beginning of the cycle and switched off at the moment the cycle reaches the presetted brightness (ledBrightness) of the LED. If ledBrightness = 0 the LED is always off (we need this in a later example).

**SignalControl.ino**

```c++
const int SIGNALPIN = 13;

const int PWMTIME = 20;        // time in msec for one PWM cycle.
const int PWMINCREASE = 1;     // each PWM cycle is divided into steps of PWMINCREASE msec
int pwmCycle;                  // each PWM cycle this starts with 1 and increases each PWMINCREASE msec up to PWMTIME

unsigned long previousMillis;  // will store last time PWM cycle was updated
int ledBrightness;               // will store brightness as the PWM width value between 0 and PWMTIME

void SignalControl_Init() {
  // initialize digital pin 13 as an output.
  pinMode(SIGNALPIN, OUTPUT);
  pwmCycle = 1;
  ledBrightness = 2;  // lowest brightness for this experiment
}

void SignalControl_Blink() {
  unsigned long currentMillis = millis();                // current time
  if (currentMillis - previousMillis >= PWMINCREASE) {   // PWMINCREASE msec have passed since last time
    previousMillis = currentMillis;                      // wait for next moment
    pwmCycle = pwmCycle + PWMINCREASE;                   // next PWMINCREASE msec within one PWM cycle
    if (pwmCycle > PWMTIME) {                            // if one PWM cycle is completed, repeat by starting at 1
      pwmCycle = 1;
    };
    int ledState;
    if (ledBrightness >= pwmCycle) {   // switch LED on or off during one cycle at the moment the setting of the brightness is reached
      ledState = HIGH;                 // HIGH means set LED on
    } else {
      ledState = LOW;                  // LOW means set LED off
    }
    digitalWrite(SIGNALPIN, ledState); //set output according to ledState
  }
}

```

**10_BrightnessWithoutDelay.ino**

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

[TOP](#English)

##  11_BrightnessWithoutDelay4LEDs

The example above is extended to four ledState

**SignalControl.ino**
```c++
const int NUMBEROFPINS = 4;
const int SIGNALPINS[NUMBEROFPINS] = {13, 12, 10, 9};

const int UP = 1;              // increase brightness
const int DOWN = -1;           // decrease brightness
const int PWMTIME = 20;        // time in msec for one PWM cycle. 20 msec means 50 Hz cycle.
const int PWMINCREASE = 1;     // each PWM cycle is divided into steps of PWMINCREASE msec
int pwmCycle;                  // each PWM cycle starts with 1 and increases each PWMINCREASE msec up to PWMTIME
int brightCycle;               // count PWM cycles
int ledBrightness[NUMBEROFPINS] ; // will store brightness as the PWM width value between 0 and PWMTIME
int ledDimOrBright[NUMBEROFPINS]; // should led get brighter so UP (+1) of must it dimm DOWN (-1)

const int BRIGHTINCREASECYCLES = 2; // after BRIGHTINCREASECYCLES times a complete PWM cycle brightness is increased or decreased

unsigned long previousMillis;  // will store last time PWM cycle was updated

void SignalControl_Init() {
  // initialize digital pin 13 as an output.
  for (int i = 0; i < NUMBEROFPINS; i++) {
    pinMode(SIGNALPINS[i], OUTPUT);
    ledDimOrBright[i] = UP;
  }
  ledBrightness[0] = 1;  // some brightness for this experiment
  ledBrightness[1] = 6;  // some brightness for this experiment
  ledBrightness[2] = 11;  // some brightness for this experiment
  ledBrightness[3] = 17;  // some brightness for this experiment
  pwmCycle = 1;
  brightCycle = 0;
}

void SignalControl_Blink() {
  unsigned long currentMillis = millis();                // current time
  if (currentMillis - previousMillis >= PWMINCREASE) {   // PWMINCREASE msec have passed since last time
    previousMillis = currentMillis;                      // wait for next moment
    pwmCycle = pwmCycle + PWMINCREASE;                   // next PWMINCREASE msec within one PWM cycle
    if (pwmCycle > PWMTIME) {                            // if one PWM cycle is completed, repeat by starting at 1
      pwmCycle = 1;
      brightCycle ++;                                   // increase cycle number
      if (brightCycle > BRIGHTINCREASECYCLES) {         // it is time to increase or decrease brightness
        brightCycle = 0;
        for (int i = 0; i < NUMBEROFPINS; i++) {
          ledBrightness[i] = ledBrightness[i] + ledDimOrBright[i]; // increase or decreas brightness depening on direction
          if (ledBrightness[i] == PWMTIME) {                 // if at maximum, for now invert to dimming
            ledDimOrBright[i] = DOWN;
          };
          if (ledBrightness[i] == 1) {                       // if at minimum, for now invert to more bright. ledBrightness = 0 is used for the state off
            ledDimOrBright[i] = UP;
          };
        };
      };
    };
    for (int i = 0; i < NUMBEROFPINS; i++) {
      digitalWrite(SIGNALPINS[i], (ledBrightness[i] >= pwmCycle) ? (HIGH) : (LOW)); //set output according to the position in the cycle
    };
  };
}
```

**11_BrightnessWithoutDelay4LEDs.ino**

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

[TOP](#English)


## 12_FadingWithoutDelay

Now the example above is extended to get a fading effect.The brightness is slowely increased until maximum and then decreased at the same speed until minimum.

**SignalControl.ino**

```c++
const int SIGNALPIN = 13;

const int UP = 1;              // increase brightness
const int DOWN = -1;           // decrease brightness
const int PWMTIME = 20;        // time in msec for one PWM cycle. 20 msec means 50 Hz cycle.
const int PWMINCREASE = 1;     // each PWM cycle is divided into steps of PWMINCREASE msec
int pwmCycle;                  // each PWM cycle starts with 1 and increases each PWMINCREASE msec up to PWMTIME
int brightCycle;               // count PWM cycles
int ledBrightness;             // will store brightness as the PWM width value between 0 and PWMTIME
int ledDimOrBright;            // should led get brighter so UP (+1) of must it dimm DOWN (-1)

const int BRIGHTINCREASECYCLES = 2; // after BRIGHTINCREASECYCLES times a complete PWM cycle brightness is increased or decreased

unsigned long previousMillis;  // will store last time PWM cycle was updated

void SignalControl_Init() {
  // initialize digital pin 13 as an output.
  pinMode(SIGNALPIN, OUTPUT);
  ledBrightness = 1;
  ledDimOrBright = UP;
  pwmCycle = 1;
  brightCycle = 0;
}

void SignalControl_Blink() {
  unsigned long currentMillis = millis();                // current time
  if (currentMillis - previousMillis >= PWMINCREASE) {   // PWMINCREASE msec have passed since last time
    previousMillis = currentMillis;                      // wait for next moment
    pwmCycle = pwmCycle + PWMINCREASE;                   // next PWMINCREASE msec within one PWM cycle
    if (pwmCycle > PWMTIME) {                            // if one PWM cycle is completed, repeat by starting at 1
      pwmCycle = 1;
      brightCycle ++;                                   // increase cycle number
      if (brightCycle > BRIGHTINCREASECYCLES) {         // it is time to increase or decrease brightness
        brightCycle = 0;
        ledBrightness = ledBrightness + ledDimOrBright; // increase or decreas brightness depening on direction
        if (ledBrightness == PWMTIME) {                 // if at maximum, for now invert to dimming
          ledDimOrBright = DOWN;
        };
        if (ledBrightness == 1) {                       // if at minimum, for now invert to more bright. ledBrightness = 0 is used for the state off
          ledDimOrBright = UP;
        };
      };
    };
    digitalWrite(SIGNALPIN, (ledBrightness >= pwmCycle) ? (HIGH) : (LOW)); //set output according to the position in the cycle
  }
}
```

The big change between this code and the previous example starts after **pwmCycle = 1;** Also not the improvement at the bottom with a so called 'conditional assignment'.
 Use this program to experiment with fade timing.

**12_FadingWithoutDelay.ino**

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

[TOP](#English)

## 13_FadingWithoutDelay4LEDs

Now we extend as previously done the exampel over 4 LEDs.

**SignalControl.ino**

```c++
const int NUMBEROFPINS = 4;
const int SIGNALPINS[NUMBEROFPINS] = {13, 12, 10, 9};

const int UP = 1;              // increase brightness
const int DOWN = -1;           // decrease brightness
const int PWMTIME = 20;        // time in msec for one PWM cycle. 20 msec means 50 Hz cycle.
const int PWMINCREASE = 1;     // each PWM cycle is divided into steps of PWMINCREASE msec
int pwmCycle;                  // each PWM cycle starts with 1 and increases each PWMINCREASE msec up to PWMTIME
int brightCycle;               // count PWM cycles
int ledBrightness[NUMBEROFPINS] ; // will store brightness as the PWM width value between 0 and PWMTIME
int ledDimOrBright[NUMBEROFPINS]; // should led get brighter so UP (+1) of must it dimm DOWN (-1)

const int BRIGHTINCREASECYCLES = 2; // after BRIGHTINCREASECYCLES times a complete PWM cycle brightness is increased or decreased

unsigned long previousMillis;  // will store last time PWM cycle was updated

void SignalControl_Init() {
  // initialize digital pin 13 as an output.
  for (int i = 0; i < NUMBEROFPINS; i++) {
    pinMode(SIGNALPINS[i], OUTPUT);
    ledDimOrBright[i] = UP;
  }
  ledBrightness[0] = 1;  // some brightness for this experiment
  ledBrightness[1] = 6;  // some brightness for this experiment
  ledBrightness[2] = 11;  // some brightness for this experiment
  ledBrightness[3] = 17;  // some brightness for this experiment
  pwmCycle = 1;
  brightCycle = 0;
}

void SignalControl_Blink() {
  unsigned long currentMillis = millis();                // current time
  if (currentMillis - previousMillis >= PWMINCREASE) {   // PWMINCREASE msec have passed since last time
    previousMillis = currentMillis;                      // wait for next moment
    pwmCycle = pwmCycle + PWMINCREASE;                   // next PWMINCREASE msec within one PWM cycle
    if (pwmCycle > PWMTIME) {                            // if one PWM cycle is completed, repeat by starting at 1
      pwmCycle = 1;
      brightCycle ++;                                   // increase cycle number
      if (brightCycle > BRIGHTINCREASECYCLES) {         // it is time to increase or decrease brightness
        brightCycle = 0;
        for (int i = 0; i < NUMBEROFPINS; i++) {
          ledBrightness[i] = ledBrightness[i] + ledDimOrBright[i]; // increase or decreas brightness depening on direction
          if (ledBrightness[i] == PWMTIME) {                 // if at maximum, for now invert to dimming
            ledDimOrBright[i] = DOWN;
          };
          if (ledBrightness[i] == 1) {                       // if at minimum, for now invert to more bright. ledBrightness = 0 is used for the state off
            ledDimOrBright[i] = UP;
          };
        };
      };
    };
    for (int i = 0; i < NUMBEROFPINS; i++) {
      digitalWrite(SIGNALPINS[i], (ledBrightness[i] >= pwmCycle) ? (HIGH) : (LOW)); //set output according to the position in the cycle
    };
  };
}
```

**13_FadingWithoutDelay4LEDs.ino**

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

[TOP](#English)


## Fading on transition from one aspect to another

On receiving a command the lights of the current aspect must be dimmed during a dimming period and the lights of the new aspect must get brighter during a dimming period.
