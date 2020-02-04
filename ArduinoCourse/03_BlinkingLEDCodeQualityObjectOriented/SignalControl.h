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
