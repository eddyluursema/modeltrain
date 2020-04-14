//-----------------------------------------------------------------------------
// Copyright 2018 Peter Balch
// subject to the GNU General Public License
//-----------------------------------------------------------------------------

#include <math.h>

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

const long BAUDRATE  = 115200;  // Baud rate of UART in bps

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

const byte numberOfDigits = 6; // number of digits in the frequense
byte freqSGLo[numberOfDigits] = {0, 0, 0, 1, 0, 0}; // 1000Hz 
byte freqSGHi[numberOfDigits] = {0, 0, 0, 0, 2, 0}; // 20kHz  

const int wSine     = 0b0000000000000000;
const int wTriangle = 0b0000000000000010;
const int wSquare   = 0b0000000000101000;

int waveType = wSine;

const int SG_fsyncPin = 2;
const int SG_CLK = 3;
const int SG_DATA = 4;
const int SG_POWER = 6;
int SG_iSweep,SG_nSweep;

//-----------------------------------------------------------------------------
//returns 10^y
//-----------------------------------------------------------------------------
unsigned long Power(int y) {
  unsigned long t = 1;
  for (byte i = 0; i < y; i++)
    t = t * 10;
  return t;
}

//-----------------------------------------------------------------------------
//calculate the frequency from the array.
//-----------------------------------------------------------------------------
unsigned long calcFreq(byte* freqSG) {
  unsigned long i = 0;
  for (byte x = 0; x < numberOfDigits; x++)
    i = i + freqSG[x] * Power(x);
  return i;
}

//-----------------------------------------------------------------------------
// SG_WriteRegister
//-----------------------------------------------------------------------------
void SG_WriteRegister(word dat) {
  digitalWrite(SG_CLK, LOW);
  digitalWrite(SG_CLK, HIGH);

  digitalWrite(SG_fsyncPin, LOW);
  for (byte i = 0; i < 16; i++) {
    if (dat & 0x8000)
      digitalWrite(SG_DATA, HIGH);
    else
      digitalWrite(SG_DATA, LOW);
    dat = dat << 1;
    digitalWrite(SG_CLK, HIGH);
    digitalWrite(SG_CLK, LOW);
  }
  digitalWrite(SG_CLK, HIGH);
  digitalWrite(SG_fsyncPin, HIGH);
}

//-----------------------------------------------------------------------------
// SG_Reset
//-----------------------------------------------------------------------------
void SG_Reset() {
  delay(100);
  SG_WriteRegister(0x100);
  delay(100);
}

//-----------------------------------------------------------------------------
// SG_freqReset
//    reset the SG regs then set the frequency and wave type
//-----------------------------------------------------------------------------
void SG_freqReset(long frequency, int wave) {
  long fl = frequency * (0x10000000 / 25000000.0);
  SG_WriteRegister(0x2100);
  SG_WriteRegister((int)(fl & 0x3FFF) | 0x4000);
  SG_WriteRegister((int)((fl & 0xFFFC000) >> 14) | 0x4000);
  SG_WriteRegister(0xC000);
  SG_WriteRegister(wave);
  waveType = wave;
}

//-----------------------------------------------------------------------------
// SG_freqSet
//    set the SG frequency regs 
//-----------------------------------------------------------------------------
void SG_freqSet(long frequency, int wave) {
  long fl = frequency * (0x10000000 / 25000000.0);
  SG_WriteRegister(0x2000 | wave);
  SG_WriteRegister((int)(fl & 0x3FFF) | 0x4000);
  SG_WriteRegister((int)((fl & 0xFFFC000) >> 14) | 0x4000);
}

//-----------------------------------------------------------------------------
// SG_StepSweep
//    increment the FG frequency 
//-----------------------------------------------------------------------------
void SG_StepSweep(void) {
  if (SG_iSweep > SG_nSweep) SG_iSweep = 0;
  long f = exp((log(calcFreq(freqSGHi)) - log(calcFreq(freqSGLo)))*SG_iSweep/SG_nSweep + log(calcFreq(freqSGLo))) +0.5;
  SG_freqSet(f, waveType);
  SG_iSweep++;
}

//-----------------------------------------------------------------------------
// Sweep
//   sweeps siggen freq continuously
//   takes n mS for whole sweep
//   SDC regs are saved and restored
//   stops when receives a serial char
//-----------------------------------------------------------------------------
void Sweep(int n) {
  int fmin,fmax;
  fmin = calcFreq(freqSGLo);
  fmax = calcFreq(freqSGHi);
  int i=0; 
  do {
    long f = exp((log(fmax) - log(fmin))*i/(n-1) + log(fmin)) +0.5;
    SG_freqSet(f, waveType);
    delay(1);
    i++;
    if (i >= n) i = 0;
  } while (!Serial.available());
  
  SG_freqSet(calcFreq(freqSGLo), waveType);
}

//-----------------------------------------------------------------------------
// SerialCommand
//   if a byte is available in teh seril input buffer
//   execute it as a command
//-----------------------------------------------------------------------------
void SerialCommand(void) {
  if ( Serial.available() > 0 ) {
    char c = Serial.read();

    if ((c >= '0') && (c <= '9')) {
      for (int i=5; i>0; i--) freqSGLo[i] = freqSGLo[i-1];
      freqSGLo[0] = c - '0';
    } else {
      switch (c) {
        case 'S': waveType = wSine; SG_freqReset(calcFreq(freqSGLo), waveType); break;   // SigGen wave is sine
        case 'T': waveType = wTriangle; SG_freqReset(calcFreq(freqSGLo), waveType); break;   // SigGen wave is triangle
        case 'Q': waveType = wSquare; SG_freqReset(calcFreq(freqSGLo), waveType); break;   // SigGen wave is square
        case 'R': SG_Reset();  break;   // SigGen reset
        case 'M': for (int i=0; i<=5; i++) freqSGHi[i] = freqSGLo[i]; break;   // move freq to high array
        case 'G': Sweep(1000);  break; // sweep SigGen
        case 'H': Sweep(5000);  break; // sweep SigGen
        case 'I': Sweep(20000);  break; // sweep SigGen

        default: return;
      }
    }
  }
}

//-----------------------------------------------------------------------------
// InitSigGen
//-----------------------------------------------------------------------------
void InitSigGen(void) {
  pinMode(SG_POWER, OUTPUT);
  digitalWrite(SG_POWER, HIGH);

  pinMode(SG_DATA, OUTPUT);
  pinMode(SG_CLK, OUTPUT);
  pinMode(SG_fsyncPin, OUTPUT);
  digitalWrite(SG_fsyncPin, HIGH);
  digitalWrite(SG_CLK, HIGH);
  SG_Reset();
  SG_freqReset(calcFreq(freqSGLo), waveType);
}

//-----------------------------------------------------------------------------
// Main routines
// The setup function
//-----------------------------------------------------------------------------
void setup (void) {
  // Open serial port with a baud rate of BAUDRATE b/s
  Serial.begin(BAUDRATE);

  Serial.println("SigGen " __DATE__); // compilation date
  Serial.println("OK");

  pinMode(LED_BUILTIN, OUTPUT);

  InitSigGen();
}

//-----------------------------------------------------------------------------
// Main routines
// loop
//-----------------------------------------------------------------------------
void loop (void) {
  SerialCommand();
}
