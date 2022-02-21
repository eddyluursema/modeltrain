/*
  All the setup and functions needed to use the OLED screen
  Print is scalable in several sizes. With size 2 compromises are made in number of characters shown
*/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setupOLED () {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Speedometer V0.1");  //print program, version and author
  display.setCursor(0, 17);
  display.println("Eddy Luursema");
  display.display();
  delay(4000);
}


void printOutput(int scaleSetting, float currentSpeed, float averageSum, int averageCount, state passState) {
  String outputOLED;
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  outputOLED = outputOLED + printScale(scaleSetting) + " ";
  if (passState != NONE) {
    if (passState == LEFTIN) {
      outputOLED = outputOLED + ">> ";
    } else {
      outputOLED = outputOLED + "<< ";
    }
  } else {
    outputOLED = outputOLED + String(currentSpeed, 1);
    if (outputOLED.length() > 6) {  //string does not fit with km/h so print kmh
      outputOLED = outputOLED + "kmh";
    } else
      outputOLED = outputOLED + "km/h";
  }
  display.print(outputOLED);
  display.setCursor(0, 17);
  if (averageCount >= 1) {          //average can be calculated
    display.print(averageSum / averageCount);
    display.print(" ");
    display.print("#");
    display.print(averageCount);
  }
  display.display();
}
