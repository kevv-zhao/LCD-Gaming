/*--------------------------------------------------------------------
Name:   Kevin Zhao
Date:   2022, January 19
File:   pong_and_sketch.cpp

Purp: Demonstrates the use of Adafruit 1.8" (128x160 pixels) TFT Display 
      using the Adafruit GFX and ST7735 libraries to be used to make an
      Etch-a-Sketch and Pong Game. 

Doc:  Used seesaw_shield18_test.ino to get initialization values, 
      and uses the Adafruit GFX, Adafruit ST7735, and Adafruit
      BusIO Libraries, Prof. Falkinburg
--------------------------------------------------------------------*/

#include <Arduino.h>         // jlf added for vs_code
#include <Wire.h>            // jlf added for vs_code
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>
#include "joystick_lib.h"

// LCD Pins
#define TFT_CS    10
#define TFT_RST   9 
#define TFT_DC    8
// Joystick Pins
#define VRx   PIN0  //A0 pin
#define VRy   PIN1  //A1 pin

int xVal;
int yVal;

// Create class named tft of type Adafruit_ST7735
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Function Prototypes
void Display_Menu(void);

// Etch-a-Sketch Cursor Position
int16_t brushPos[2];
int16_t color[] = {ST77XX_RED, ST77XX_ORANGE, ST77XX_YELLOW, ST77XX_GREEN, 
ST7735_CYAN, ST7735_BLUE, ST7735_MAGENTA, ST7735_WHITE, ST77XX_BLACK};

void setup() {
  Serial.begin(9600);

  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.fillScreen(ST77XX_BLACK);

  // Display Welcome Screen
  tft.setTextWrap(true);
  tft.setRotation(1); // Rotate view 270 degrees

  brushPos[0] = tft.width()/2 - 2; brushPos[1] = tft.height()/2 - 2;
  // Initialize ADC functionality
  adcInit();

  // Display_Menu();
}

void loop() {
  tft.fillRect(brushPos[0], brushPos[1], 4, 4, color[0]);

  // Obtaining analog values and changing range to -512 to +512
  xVal = readAnalogInput(VRx) - 511;
  yVal = readAnalogInput(VRy) - 511;

  // Increment the cursor position based off the joystick position and draw a new square
  if((brushPos[0]+(xVal*3/511) >= 0 && xVal < -20) || (brushPos[0]+(xVal*3/511) <= tft.width()-4 && xVal > 20)) {
    brushPos[0] = brushPos[0] + (xVal*3/511);
  }
  if((brushPos[1]+(yVal*3/511) >= 0 && yVal < -20) || (brushPos[1]+(yVal*3/511) <= tft.height()-4 && yVal > 20)) {
    brushPos[1] = brushPos[1] + (yVal*3/511);
  }
  delay(100);
}

void Display_Menu(void) {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(1);
  tft.setCursor(26, 20);
  tft.println("    LCD Gaming");
  tft.setCursor(23, 29);
  tft.println("   Select a Game");

  tft.setCursor(0, 60);
  tft.println("PONG");
  tft.println("Etch-a-Sketch");
  return;
}
