// pressing and releasing of scale button is handled with deboucing

const int CONTROLPINSCALE = A0;
BUTTONSTATE scaleButton;
long scaleButtonActionMillis;

void setupScaleButton() {
  pinMode(CONTROLPINSCALE, INPUT_PULLUP);
  scaleButton = OPEN;
}

BUTTONSTATE testScaleButton() {
  if ((scaleButton == OPEN) && (digitalRead(CONTROLPINSCALE) == 0)) {
    //button pressed first time
    scaleButton = ACTION;
    scaleButtonActionMillis = millis();
  } else
  if (scaleButton == ACTION) {  // is this state only once so main program can take action
    scaleButton = TOCLOSE;
  } else 
  if ((scaleButton == TOCLOSE) && (millis() - scaleButtonActionMillis > DEBOUNCE)) {
    scaleButton = CLOSED;
  } else
  if ((scaleButton == CLOSED) && (digitalRead(CONTROLPINSCALE) == 1)) {
    //button pressed first time
    scaleButton = TOOPEN;
    scaleButtonActionMillis = millis();
  } else 
  if ((scaleButton == TOOPEN) && (millis() - scaleButtonActionMillis > DEBOUNCE)) {
    scaleButton = OPEN;
  }
  return scaleButton;
}
