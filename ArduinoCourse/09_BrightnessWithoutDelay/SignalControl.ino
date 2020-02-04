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
