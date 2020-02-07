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
