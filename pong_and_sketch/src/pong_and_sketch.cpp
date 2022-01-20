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
#define SW    PIN2  //Digital 2 pin

int xVal;
int yVal;

// Create class named tft of type Adafruit_ST7735
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Function Prototypes
void Display_Menu(void);

// Etch-a-Sketch Cursor Position and Color Pallet
int16_t brushPos[2];
int16_t brushPrev[2];
uint16_t pallet[] = {ST77XX_RED, ST77XX_ORANGE, ST77XX_YELLOW, ST77XX_GREEN, 
ST7735_CYAN, ST7735_BLUE, ST7735_MAGENTA, ST7735_WHITE, ST77XX_BLACK};
int color = 0;

void setup() {
  Serial.begin(9600);

  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.fillScreen(ST77XX_BLACK);

  // Display Welcome Screen
  tft.setTextWrap(true);
  tft.setRotation(1); // Rotate view 90 degrees
  // Initializing the brush position based off the current dimensions of the screen.
  brushPos[0] = tft.width()/2 - 2; brushPos[1] = tft.height()/2 - 2;
  brushPrev[0] = brushPos[0]; brushPrev[1] = brushPos[1];
  tft.fillRect(brushPos[0], brushPos[1], 4, 4, ST7735_BLACK);
  tft.fillRect(brushPos[0], brushPos[1], 3, 3, pallet[color]);

  // Initialize ADC functionality and switch input
  adcInit();
  DDRD &= ~(1 << SW);
  PORTD |= (1 << SW);

  // Display_Menu();
}

void loop() {
  // Change the brush color if the joystick switch is pressed
  if(!(PIND & (1 << SW))) {
    color = (color+1) % 9;
    if(color != 8) {
      tft.fillRect(brushPos[0], brushPos[1], 4, 4, ST7735_BLACK);
      tft.fillRect(brushPos[0], brushPos[1], 3, 3, pallet[color]);
    } else {
      tft.fillRect(brushPos[0], brushPos[1], 4, 4, ST7735_WHITE);
      tft.fillRect(brushPos[0], brushPos[1], 3, 3, pallet[color]);
    }
  }
  // Obtaining analog values and changing range to -512 to +512
  xVal = readAnalogInput(VRx) - 511;
  yVal = readAnalogInput(VRy) - 511;

  // Increment the cursor position based off the joystick position and draw a new square
  brushPrev[0] = brushPos[0]; brushPrev[1] = brushPos[1];
  if((brushPos[0] > 0 && xVal < -20) || (brushPos[0] <= tft.width()-4 && xVal > 20)) {
    brushPos[0] = brushPos[0] + (xVal*3/511);
  }
  if((brushPos[1] >= 0 && yVal < -20) || (brushPos[1] <= tft.height()-4 && yVal > 20)) {
    brushPos[1] = brushPos[1] + (yVal*3/511);
  }

  // Draw a square in the current brush position only if the joystick has changed the brush position
  if(xVal < -20 || xVal > 20 || yVal < -20 || yVal > 20) {
    tft.fillRect(brushPrev[0], brushPrev[1], 4, 4, pallet[color]);
    if(color != 8) {
      tft.fillRect(brushPos[0], brushPos[1], 4, 4, ST7735_BLACK);
      tft.fillRect(brushPos[0], brushPos[1], 3, 3, pallet[color]);
    } else {
      tft.fillRect(brushPos[0], brushPos[1], 4, 4, ST7735_WHITE);
      tft.fillRect(brushPos[0], brushPos[1], 3, 3, pallet[color]);
    }
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
