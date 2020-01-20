/**********************************************************************

  SerialCommand.h
  COPYRIGHT (c) 2013-2016 Gregg E. Berman

  Part of DCC++ BASE STATION for the Arduino

**********************************************************************/

#ifndef SerialCommand_h
#define SerialCommand_h

#include "PacketRegister.h"
#include "CurrentMonitor.h"

#define  MAX_COMMAND_LENGTH         30
const int MINSPEED = -120;
const int MAXSPEED = 120;
const int SPEEDSTEP = 20;

struct SerialCommand {
  static char commandString[MAX_COMMAND_LENGTH + 1];
 static volatile RegisterList *mRegs, *pRegs;
  static CurrentMonitor *mMonitor;
  static void init(volatile RegisterList *, volatile RegisterList *, CurrentMonitor *);
  static void parse(char *);
  static void process();
  static void testFunctionKeys(char c);
}; // SerialCommand

#endif
