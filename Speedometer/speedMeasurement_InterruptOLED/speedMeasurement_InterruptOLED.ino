/*
  Speedometer by Eddy Luursema 2022 Febrary
   
  Simple speed measuring system for model train control using two IR gatesways, two buttons and an OLED
  This example uses interrupts on pin2 and 3 of the Atmel386P which can be configured for interrupts for a locomotive coming from left of right
*/
enum SCALETYPE {G = 24, O = 48, S = 64, H0 = 87, N = 160, Z = 220}; //these are the scales system supports, adding a new one means also change controlScaleFunctions.ino
SCALETYPE scaleSetting;                                             //actual scale that is set

const int NRBUTTONS = 2;                                  //system has two buttons
int buttonStates[NRBUTTONS];                              //buttonstate is used to prevent bouncing but also as semaphore
enum BUTTONTYPE {SCALEBUTTON, RESETBUTTON};               //name of the buttons in this program
enum BUTTONSTATE {OPEN, ACTION, TOCLOSE, CLOSED, TOOPEN}; //button can be open, closed, bouncing from open to close or open and action

const float sensorLength = 348.0;   //the distance between the sensors in mm specific for each construction
enum state {NONE, LEFTIN, RIGHTIN}; //possible statuses of the loc being outside the gateway, entered from left or entered from right
volatile state passState;           //catual status of the loc; is volatile because is used as semaphore
const int GLITCH = 30000;           //the loc must pass in 30 seconds or passing of IR will be treated as a glitch and loc is supposed to be outside

long previousMillis;          //timestamp of previous passing
long currentMillis;           //timestamp of previous passing
long intervalMillis;          //interval of passing two IR-gateways
float currentSpeed;           //calculated speed according to scale
float averageSpeed;           //average speed over multiple measurements; button can reset average
int averageCount;             //number of measurements
volatile bool printDirection; //indication that main program must print direction; is volatile because is used as semaphore

void setup() {
  setupButtons();         //initialise input ports
  setupOLED();            //initialise OLED; show hello for a few seconds
  setupIRGateWay();       //initialise IR input ports and interrupts
  scaleSetting = N;       //my track is scale N so that is the default
  passState = NONE;       //start without locomotive between gateways
  printDirection = false; //used as semaphore between interrupt routine and main loop. If true print direction
  intervalMillis = 0;     //used as semaphore between interrupt routine and main loop. If unequal 0 print interval and speed
  averageSpeed = 0.0;
  averageCount = 0;
  printOutput(scaleSetting, 0, averageSpeed, averageCount, passState); //print scale and average zero
}

void loop() {
  testButtons();                                //test if any button is pressed
  if (buttonStates[SCALEBUTTON] == ACTION) {    //scale button pressed?
    scaleSetting = setNextScale(scaleSetting);  //set the next scale and print it
    printOutput(scaleSetting, currentSpeed, averageSpeed, averageCount, NONE);
    buttonStates[SCALEBUTTON] = TOCLOSE;        //semaphore: button pressed was detected by function testButtons. Main loop handles action and set state to TOCLOSE so function testButtons can catch debounce
  }
  if (buttonStates[RESETBUTTON] == ACTION) {    //reset button pressed?
    averageSpeed = 0;                           //reset average and print it
    averageCount = 0;
    currentSpeed = 0;
    printOutput(scaleSetting, currentSpeed, averageSpeed, averageCount, passState);
    buttonStates[RESETBUTTON] = TOCLOSE;        //reset semaphore
  }
  if (printDirection) {       //semaphore indicates one of the interrupt functions has direction to print
    printOutput(scaleSetting, currentSpeed, averageSpeed, averageCount, passState);
    printDirection = false;   //reset semaphore so direction is only printed once
  }
  if (intervalMillis != 0) {  //semaphore indicates one of the interrupt functions has interval and speed to print
    currentSpeed = calculateSpeed(sensorLength, intervalMillis, scaleSetting);
    averageSpeed = averageSpeed + currentSpeed;
    averageCount++;
    printOutput(scaleSetting, currentSpeed, averageSpeed, averageCount, NONE);
    intervalMillis = 0;       //reset semaphore so interval is only printed once
  }
  if ((passState != NONE) && (millis() - previousMillis > GLITCH)) {  //both IR gatways not within 30 seconds?
    passState = NONE;                                                 //glitch in IR so assume loc is outside of gateway
    printOutput(scaleSetting, currentSpeed, averageSpeed, averageCount, NONE);
  }
}
