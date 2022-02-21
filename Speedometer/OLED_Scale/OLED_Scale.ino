/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

enum SCALE {G = 24, O = 48, S = 64, H0 = 87, N = 160, Z = 220};
SCALE scaleSetting; //actual scale set
enum BUTTONSTATE {OPEN, ACTION, TOCLOSE, CLOSED, TOOPEN};
 
const int DEBOUNCE = 10;
float averageSum = 0;
int averageCount = 0;



void printOutput(SCALE scaleSetting, float currentSpeed, float averageSum, int averageCount) {
  display.clearDisplay();
  display.setTextSize(1); //size 1 does  work; 2 and bigger to big
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Speedometer");
  display.setCursor(0, 10);
  display.print(printScale(scaleSetting));
  display.print(" ");
  display.print(currentSpeed);
  display.print(" km/h");
  display.setCursor(0, 25);
  if (averageCount >= 1) {
    display.print(averageSum / averageCount);
    display.print("  (");
    display.print(averageCount);
    display.println(")");
  }
  display.display();
}

void setup() {
  setupScaleButton();
  setupResetButton();
  scaleSetting = N;
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  printOutput(scaleSetting, 0, averageSum, averageCount);
}

void loop() {
  if (testScaleButton() == ACTION) {
    scaleSetting = setNextScale(scaleSetting);  // set the next scale
  }
  if (testResetButton() == ACTION) {
    averageSum = 0;  // set the next scale
    averageCount = 0;
  }


  averageSum = averageSum + averageCount;
  averageCount++;
  printOutput(scaleSetting, 0, averageSum, averageCount);
}
