/*
  All the setup and functions needed to use the two buttons with deboucing. Software is capable of handling more buttons
*/
int buttonPins[NRBUTTONS] = {A0, A1}; //pins to which buttons are connected
long buttonActionMillis[NRBUTTONS];   //time first action on given button
const int DEBOUNCE = 10;              //10 msec for debouncing

void setupButtons() {
  for (int button = 0; button < NRBUTTONS; button++) {
    pinMode(buttonPins[button], INPUT_PULLUP);  //set pin to input
    buttonStates[button] = OPEN;                //button state is default not pressed
  }
}

void testButtons() {
  for (int button = 0; button < NRBUTTONS; button++) {                              //wal;k through all buttons
    if ((buttonStates[button] == OPEN) && (digitalRead(buttonPins[button]) == 0)) { //was button pressed?
      buttonStates[button] = ACTION;                                                //this state is used as semaphore between this function and main loop
      buttonActionMillis[button] = millis();                                        //save moment of first press
    } else if ((buttonStates[button] == TOCLOSE) &&
               (millis() - buttonActionMillis[button] > DEBOUNCE)) {                //button was closing and debounce time has passed?
      buttonStates[button] = CLOSED;                                                //button is now officially closed
    } else if ((buttonStates[button] == CLOSED) &&                                  //button is opening?
               (digitalRead(buttonPins[button]) == 1)) {
      //button pressed first time
      buttonStates[button] = TOOPEN;
      buttonActionMillis[button] = millis();
    } else if ((buttonStates[button] == TOOPEN) &&
               (millis() - buttonActionMillis[button] > DEBOUNCE)) {                //button was opening and debounce time has passed?
      buttonStates[button] = OPEN;                                                  //button is now officially opened
    }
  }
}

BUTTONSTATE getButtonState(BUTTONTYPE button) {
  return buttonStates[button];
}
