/* This sketch is an example of how to use one single LED to represent several status situations


*/
const int ON = 1;
const int OFF = 0;

const int NUMBEROFPINS = 1;
const int SIGNALPINS[NUMBEROFPINS] = {13};
byte ledStatus[NUMBEROFPINS];         // keep track if LED is ON or OFF

const int CYCLE = 1000;               //one cycle takes 1000 ms
const int MAXBLINKPATTERN = 8;        // maximum number of 1 0 situations during one cycle
const int BLINKPATTERN [NUMBEROFPINS][MAXBLINKPATTERN] = {  //remember we start with LED ON
  {100, 200, 300, 400, 500, 600, 1000, 1000}
};

int nextBlinkPattern[NUMBEROFPINS];   // keep record for each pin what the next time period in BLINKPATTERN is

void setup() {
  for (int i = 0; i < NUMBEROFPINS; i++)
  {
    pinMode(SIGNALPINS[i], OUTPUT);
  };
  Serial.begin(9600);
}

unsigned long previousMillis = 0;

void loop() {
  for (int i = 0; i < NUMBEROFPINS; i++)
  {
    ledStatus[i] = ON;                          //start with all lED's on
    digitalWrite(SIGNALPINS[i], ledStatus[i]);  //set LED
    nextBlinkPattern[i] = 0;                    //start at beginning of BLINKPATTERN for each LED
  }
  unsigned long currentMillis = millis();
  while (previousMillis + CYCLE > currentMillis) {
    for (int i = 0; i < NUMBEROFPINS; i++)  //walk through all lED's
    {
      if (previousMillis + BLINKPATTERN[i][nextBlinkPattern[i]] < currentMillis) {  //time to flip?
        /*Serial.println(previousMillis);
        Serial.print("nextBlinkPattern[i] ");
        Serial.println(nextBlinkPattern[i]);
        Serial.println(BLINKPATTERN[i][nextBlinkPattern[i]]);
        Serial.print(""
        Serial.println(currentMillis);
        Serial.println();*/
        ledStatus[i] = (ledStatus[i] == ON) ? OFF : ON;   // invert LED
        digitalWrite(SIGNALPINS[i], ledStatus[i]);        // set lED
        nextBlinkPattern[i] = nextBlinkPattern[i] + 1;    // skip nextBlinkPattern to next period
      }
    }
    currentMillis = millis(); // check if time has advanced
  }
  previousMillis = currentMillis;
}
