const int SIGNALPIN = 13;

const int PWMTIME = 20;        // time in msec for one PWM cycle. 20 msec means 50 Hz cycle.
const int PWMINCREASE = 1;     // each PWM cycle is divided into steps of PWMINCREASE msec
int pwmCycle;                  // each PWM cycle this starts with 1 and increases each PWMINCREASE msec up to PWMTIME
int brightCycle;               // count PWM cycles
const int BRIGHTINCREASECYCLES = 2; // after BRIGHTINCREASECYCLES times a complete PWM cycle brightness is increased or decreased

unsigned long previousMillis;  // will store last time PWM cycle was updated

void SignalControl_Init() {
  // initialize digital pin 13 as an output.
  pinMode(SIGNALPIN, OUTPUT);
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
      brightCycle ++;                            // increase cycle number
      if (brightCycle > BRIGHTINCREASECYCLES) {  // it is time to increase or decrease brightness
        brightCycle = 0;
        if ((ledBrightness < PWMTIME) && (ledDimOrBright == UP)) { // as long not at maximum
          ledBrightness = ledBrightness + 1;         // increase brightness
          if (ledBrightness == PWMTIME) {                         // if at maximum, for now invert to dimming
            ledDimOrBright = DOWN;
          }
        };
        if ((ledBrightness > 1) && (ledDimOrBright == DOWN)) { // as long not at minimum
          ledBrightness = ledBrightness - 1;    // increase brightness
          if (ledBrightness == 1) {                          // if at maximum, for now invert to dimming
            ledDimOrBright = UP;
          }
        };
      };
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
