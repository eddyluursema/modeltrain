///////////////////////////////////////////////////////
// From: https://rudysmodelrailway.wordpress.com/2015/10/23/dcc-sniffer-packet-analyser-with-arduino/
// Adapted with timestamp, colors Eddy Luursema March 2019

///////////////////////////////////////////////////////
// DCC packet analyze: Ruud Boer, October 2015
// DCC packet capture: Robin McKay, March 2014
//
// The DCC signal is detected on Arduino digital pin 2
//
// Set the Serial Monitor Baud Rate to 38400 !!
//
// Keyboard commands that can be sent via Serial Monitor:
// 1 = 1s refresh time
// 2 = 2s
// 3 = 4s (default)
// 4 = 8s
// 5 = 16s
// 6 = 4 DCC packet buffer
// 7 = 8
// 8 = 16
// 9 = 32 (default)
// 0 = 64
// a = show accessory packets toggle
// c = show colors on terminal toggle
// l = show locomotive packets toggle
//
////////////////////////////////////////////////////////

byte refreshTime = 4; // Time between DCC packets buffer refreshes in s
byte packetBufferSize = 32; // DCC packets buffer size

#define TIMER_PRESCALER 64
#define DccBitTimerCount (F_CPU * 80L / TIMER_PRESCALER / 1000000L)
// 16000000 * 80 / 64 / 1000000 = 20; 20 x 4usecs = 80us

boolean packetEnd;
boolean preambleFound;

const byte bitBufSize = 50; // number of slots for bits
volatile byte bitBuffer[bitBufSize];
volatile byte bitBuffHead = 1;
volatile byte bitBuffTail = 0;

byte pktByteCount = 0;
byte packetBytesCount;
byte preambleOneCount;
byte dccPacket[6]; // buffer to hold a packet
byte instrByte1;
byte decoderType; //0=Loc, 1=Acc
byte bufferCounter = 0;
byte isDifferentPacket = 0;
byte showLoc = 1;
byte showAcc = 1;
byte showCol = 1;


unsigned int decoderAddress;
unsigned int packetBuffer[64];
unsigned int packetNew = 0;

unsigned long timeToRefresh = millis() + refreshTime * 1000;

// from: https://misc.flogisoft.com/bash/tip_colors_and_formatting
#define HELLO_COLOR "\e[97m"      //white
#define TIMEPROMPT_COLOR "\e[97m" //white
#define DCCIDLE_COLOR "\e[93m"    //yellow
#define LOC_COLOR "\e[31m"        //red
#define LOCFUN_COLOR "\e[92m"     //green
#define LOCCV_COLOR "\e[95m"      //magenta
#define ACC_COLOR "\e[94m"        //blue

//========================

void getPacket() {
  preambleFound = false;
  packetEnd = false;
  packetBytesCount = 0;
  preambleOneCount = 0;
  while (! packetEnd) {
    if (preambleFound) getNextByte();
    else checkForPreamble();
  }
}

//========================

void checkForPreamble() {
  byte nextBit = getBit();
  if (nextBit == 1) preambleOneCount++;
  if (preambleOneCount < 10 && nextBit == 0) preambleOneCount = 0;
  if (preambleOneCount >= 10 && nextBit == 0) preambleFound = true;
}

//========================

void getNextByte() {
  byte newByte = 0;
  for (byte n = 0; n < 8; n++) newByte = (newByte << 1) + getBit();
  packetBytesCount ++;
  dccPacket[packetBytesCount] = newByte;
  dccPacket[0] = packetBytesCount;
  if (getBit() == 1) packetEnd = true;
}

//========================

byte getBit() {
  // gets the next bit from the bitBuffer
  // if the buffer is empty it will wait indefinitely for bits to arrive
  byte nbs = bitBuffHead;
  while (nbs == bitBuffHead) byte nbs = nextBitSlot(bitBuffTail); //Buffer empty
  bitBuffTail = nbs;
  return (bitBuffer[bitBuffTail]);
}

//========================

void beginBitDetection() {
  TCCR0A &= B11111100;  // timer 0 is used
  attachInterrupt(0, startTimer, RISING);
}

//========================

void startTimer() {
  OCR0B = TCNT0 + DccBitTimerCount;
  TIMSK0 |= B00000100;
  TIFR0  |= B00000100;
}

//========================

ISR(TIMER0_COMPB_vect) {
  byte bitFound = ! ((PIND & B00000100) >> 2);
  TIMSK0 &= B11111011;
  byte nbs = nextBitSlot(bitBuffHead);
  if (nbs == bitBuffTail) return;
  else {
    bitBuffHead = nbs;
    bitBuffer[bitBuffHead] = bitFound;
  }
}

//========================

byte nextBitSlot(byte slot) {
  slot ++;
  if (slot >= bitBufSize) slot = 0;
  return (slot);
}

//========================

void printPacket() {
  Serial.print(" ");
  for (byte n = 1; n < pktByteCount; n++) {
    Serial.print(" ");
    Serial.print(dccPacket[n], BIN);
  }
  Serial.println(" ");
}

//========================

void refreshBuffer() {
  timeToRefresh = millis() + refreshTime * 1000;
  for (byte n = 0; n < packetBufferSize; n++) packetBuffer[n] = 0;
  bufferCounter = 0;
}

void printColor(String tPrint) {
  if (showCol) {
    Serial.print(tPrint);
  }
}

void printLoc(String color, int decoderAddress) {  //print Loc + decoderadress if needed in color
  printColor(color);
  Serial.print("Loc ");
  Serial.print(decoderAddress);
}

void printTime() {  /*print time since startup*/
  char charBuf[50];
  unsigned long allSeconds = millis() / 1000;
  int runHours = allSeconds / 3600;
  int secsRemaining = allSeconds % 3600;
  int runMinutes = secsRemaining / 60;
  int runSeconds = secsRemaining % 60;
  sprintf(charBuf, "%02d:%02d:%02d > ", runHours, runMinutes, runSeconds);
  printColor(TIMEPROMPT_COLOR);
  Serial.print(charBuf);
}

//========================

void setup() {
  Serial.begin(38400); // 38400 when on DCC, 9600 when testing on 123Circuits !!!!!!!!!!!!!!!!!!!!!!!
  printColor(HELLO_COLOR);
  Serial.println("DCC Packet Analyze started");

  beginBitDetection(); //Uncomment this line when on DCC !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

//====================

void loop() {
  getPacket(); //Uncomment this line when on DCC !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  byte speed;
  byte checksum = 0;

  if (millis() > timeToRefresh) refreshBuffer();

  /* Dummy packet for test purposes. Comment when on DCC !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // Loc 1782 CV Write 3 128
    dccPacket[0]=6;
    dccPacket[1]=B11000111;
    dccPacket[2]=B01101110;
    dccPacket[3]=B11101100;
    dccPacket[4]=B00000011;
    dccPacket[5]=B10000000;
    dccPacket[6]=B11111111;
  */
  pktByteCount = dccPacket[0];
  if (!pktByteCount) return; // No new packet available

  for (byte n = 1; n <= pktByteCount; n++) checksum ^= dccPacket[n];
  //checksum=0; //Comment this line when on DCC !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  if (checksum) return; // Invalid Checksum

  else { // There is a new packet with a correct checksum
    isDifferentPacket = 1;
    for (byte n = 0; n < packetBufferSize ; n++) { // Check if packet is not already in the buffer.
      // The checksum byte is used for the test, not ideal, some new packets may not show (only 256 different checksums)
      if (dccPacket[pktByteCount] == packetBuffer[n]) isDifferentPacket = 0;
    }

    if (isDifferentPacket) {  // packet does not yet exist in the packet buffer
      packetBuffer[bufferCounter] = dccPacket[pktByteCount]; // add new packet to the buffer
      bufferCounter = (++bufferCounter) & (packetBufferSize - 1);

      printTime();

      if (dccPacket[1] == B11111111) { //Idle packet
        printColor(DCCIDLE_COLOR);
        Serial.println("Idle ");
        return;
      }
      if (!bitRead(dccPacket[1], 7)) { //bit7=0 -> Loc Decoder Short Address
        decoderAddress = dccPacket[1];
        instrByte1 = dccPacket[2];
        decoderType = 0;
      }
      else {
        if (bitRead(dccPacket[1], 6)) { //bit7=1 AND bit6=1 -> Loc Decoder Long Address
          decoderAddress = 256 * (dccPacket[1] & B00000111) + dccPacket[2];
          instrByte1 = dccPacket[3];
          decoderType = 0;
        }
        else { //bit7=1 AND bit6=0 -> Accessory Decoder
          decoderAddress = dccPacket[1] & B00111111;
          instrByte1 = dccPacket[2];
          decoderType = 1;
        }
      }
      if (decoderType) { // Accessory Basic
        if (showAcc) {
          printColor(ACC_COLOR);
          if (instrByte1 & B10000000) { // Basic Accessory
            decoderAddress = (((~instrByte1)&B01110000) << 2) + decoderAddress;
            byte port = (instrByte1 & B00000110) >> 1;
            Serial.print("Acc ");
            Serial.print((decoderAddress - 1) * 4 + port + 1);
            Serial.print(" ");
            Serial.print(decoderAddress);
            Serial.print(":");
            Serial.print(port);
            Serial.print(" ");
            Serial.print(bitRead(instrByte1, 3));
            if (bitRead(instrByte1, 0)) Serial.print(" On");
            else Serial.print(" Off");
          }
          else { // Accessory Extended NMRA spec is not clear about address and instruction format !!!
            Serial.print("Acc Ext ");
            decoderAddress = (decoderAddress << 5) + ((instrByte1 & B01110000) >> 2) + ((instrByte1 & B00000110) >> 1);
            Serial.print(decoderAddress);
            Serial.print(" Asp ");
            Serial.print(dccPacket[3], BIN);
          }
          printPacket();
        }
      }
      else { // Loc / Multi Function Decoder
        if (showLoc) {
          byte instructionType = instrByte1 >> 5;
          switch (instructionType) {

            case 0:
              printLoc(LOC_COLOR, decoderAddress);
              Serial.print(" Control ");
              break;

            case 1: // Advanced Operations
              printLoc(LOC_COLOR, decoderAddress);
              if (instrByte1 == B00111111) { //128 speed steps
                if (bitRead(dccPacket[pktByteCount - 1], 7)) Serial.print(" Forw128 ");
                else Serial.print(" Rev128 ");
                byte speed = dccPacket[pktByteCount - 1] & B01111111;
                if (!speed) Serial.print(" Stop ");
                else if (speed == 1) Serial.print(" E-stop ");
                else Serial.print(speed - 1);
              }
              else if (instrByte1 == B00111110) { //Speed Restriction
                if (bitRead(dccPacket[pktByteCount - 1], 7)) Serial.print(" On ");
                else Serial.print(" Off ");
                Serial.print(dccPacket[pktByteCount - 1])&B01111111;
              }
              break;

            case 2: // Reverse speed step
              printLoc(LOC_COLOR, decoderAddress);
              speed = ((instrByte1 & B00001111) << 1) - 3 + bitRead(instrByte1, 4);
              if (speed == 253 || speed == 254) Serial.print(" Stop ");
              else if (speed == 255 || speed == 0) Serial.print(" E-Stop ");
              else {
                Serial.print(" Rev ");
                Serial.print(speed);
              }
              break;

            case 3: // Forward speed step
              printLoc(LOC_COLOR, decoderAddress);
              speed = ((instrByte1 & B00001111) << 1) - 3 + bitRead(instrByte1, 4);
              if (speed == 253 || speed == 254) Serial.print(" Stop ");
              else if (speed == 255 || speed == 0) Serial.print(" E-Stop ");
              else {
                Serial.print(" Forw ");
                Serial.print(speed);
              }
              break;

            case 4: // Loc Function L-4-3-2-1
              printLoc(LOCFUN_COLOR, decoderAddress);
              Serial.print(" L F4-F1 ");
              Serial.print(instrByte1 & B00011111, BIN);
              break;

            case 5: // Loc Function 8-7-6-5
              printLoc(LOCFUN_COLOR, decoderAddress);
              if (bitRead(instrByte1, 4)) {
                Serial.print(" F8-F5 ");
                Serial.print(instrByte1 & B00001111, BIN);
              }
              else { // Loc Function 12-11-10-9
                Serial.print(" F12-F9 ");
                Serial.print(instrByte1 & B00001111, BIN);
              }
              break;

            case 6: // Future Expansions
              printLoc(LOCFUN_COLOR, decoderAddress);
              switch (instrByte1 & B00011111) {
                case 0: // Binary State Control Instruction long form
                  Serial.print(" BinStateLong ");
                  Serial.print(256 * dccPacket[pktByteCount - 1] + (dccPacket[pktByteCount - 2]&B01111111));
                  if bitRead(dccPacket[pktByteCount - 2], 7) Serial.print(" On ");
                  else Serial.print(" Off ");
                  break;
                case B00011101: // Binary State Control
                  Serial.print(" BinStateShort ");
                  Serial.print(dccPacket[pktByteCount - 1]&B01111111);
                  if bitRead(dccPacket[pktByteCount - 1], 7) Serial.print(" On ");
                  else Serial.print(" Off ");
                  break;
                case B00011110: // F13-F20 Function Control
                  Serial.print(" F20-F13 ");
                  Serial.print(dccPacket[pktByteCount - 1], BIN);
                  break;
                case B00011111: // F21-F28 Function Control
                  Serial.print(" F28-F21 ");
                  Serial.print(dccPacket[pktByteCount - 1], BIN);
                  break;
              }
              break;

            case 7:
              printLoc(LOCCV_COLOR, decoderAddress);
              Serial.print(" CV ");
              if (instrByte1 & B00010000) { // CV Short Form
                byte cvType = instrByte1 & B00001111;
                switch (cvType) {
                  case B00000010:
                    Serial.print("23 ");
                    Serial.print(dccPacket[pktByteCount - 1]);
                    break;
                  case B00000011:
                    Serial.print("24 ");
                    Serial.print(dccPacket[pktByteCount - 1]);
                    break;
                  case B00001001:
                    Serial.print("Decoder Lock ");
                    Serial.print(dccPacket[pktByteCount - 1]);
                    break;
                }
              }
              else { // CV Long Form
                int cvAddress = 256 * (instrByte1 & B00000011) + dccPacket[pktByteCount - 2] + 1;
                Serial.print(cvAddress);
                Serial.print(" ");
                switch (instrByte1 & B00001100) {
                  case B00000100: // Verify Byte
                    Serial.print("Verify ");
                    Serial.print(dccPacket[pktByteCount - 1]);
                    break;
                  case B00001100: // Write Byte
                    Serial.print("Write ");
                    Serial.print(dccPacket[pktByteCount - 1]);
                    break;
                  case B00001000: // Bit Write
                    Serial.print("Bit ");
                    if (dccPacket[pktByteCount - 2]&B00010000) Serial.print("Verify ");
                    else Serial.print("Write ");
                    Serial.print(dccPacket[pktByteCount - 1]&B00000111);
                    Serial.print(" ");
                    Serial.print((dccPacket[pktByteCount - 1]&B00001000) >> 3);
                    break;
                }
              }
              break;
          }
          printPacket();
        }
      }
    }
  }
  if (Serial.available()) {
    Serial.println(" ");
    switch (Serial.read()) {
      case 49:  //1
        Serial.println("Refresh Time = 1s");
        refreshTime = 1;
        break;
      case 50:  //2
        Serial.println("Refresh Time = 2s");
        refreshTime = 2;
        break;
      case 51:  //3
        Serial.println("Refresh Time = 4s");
        refreshTime = 4;
        break;
      case 52:  //4
        Serial.println("Refresh Time = 8s");
        refreshTime = 8;
        break;
      case 53:
        Serial.println("Refresh Time = 16s");
        refreshTime = 16;
        break;
      case 54:
        Serial.println("Buffer Size = 4");
        packetBufferSize = 2;
        break;
      case 55:
        Serial.println("Buffer Size = 8");
        packetBufferSize = 8;
        break;
      case 56:
        Serial.println("Buffer Size = 16");
        packetBufferSize = 16;
        break;
      case 57:
        Serial.println("Buffer Size = 32");
        packetBufferSize = 32;
        break;
      case 48:
        Serial.println("Buffer Size = 64");
        packetBufferSize = 64;
        break;
      case 97:  //a
        if (showAcc) showAcc = 0; else showAcc = 1;
        Serial.print("show acc packets = ");
        Serial.println(showAcc);
        break;
      case 99:  //c
        if (showCol) showCol = 0; else showCol = 1;
        Serial.print("show color = ");
        Serial.println(showCol);
        break;
      case 108: //l
        if (showLoc) showLoc = 0; else showLoc = 1;
        Serial.print("show loc packets = ");
        Serial.println(showLoc);
        break;
    }
    Serial.println(" ");
  }
}

//=====================
