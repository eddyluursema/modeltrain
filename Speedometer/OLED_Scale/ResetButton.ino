// pressing and releasing of reset button is handled with deboucing

const int CONTROLPINRESET = A1;
BUTTONSTATE resetButton;
long resetButtonActionMillis;

void setupResetButton() {
  pinMode(CONTROLPINRESET, INPUT_PULLUP);
  resetButton = OPEN;
}

BUTTONSTATE testResetButton() {
  if ((resetButton == OPEN) && (digitalRead(CONTROLPINRESET) == 0)) {
    //button pressed first time
    resetButton = ACTION;
    resetButtonActionMillis = millis();
  } else 
  if (resetButton == ACTION) {  // is this state only once so main program can take action
    resetButton = TOCLOSE;
  } else 
  if ((resetButton == TOCLOSE) && (millis() - resetButtonActionMillis > DEBOUNCE)) {
    resetButton = CLOSED;
  } else
  if ((resetButton == CLOSED) && (digitalRead(CONTROLPINRESET) == 1)) {
    //button pressed first time
    resetButton = TOOPEN;
    resetButtonActionMillis = millis();
  } else
  if ((resetButton == TOOPEN) && (millis() - resetButtonActionMillis > DEBOUNCE)) {
    resetButton = OPEN;
  }
  return resetButton;
}
