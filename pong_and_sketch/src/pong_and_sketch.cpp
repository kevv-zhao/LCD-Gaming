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
#include "etch_a_sketch.h"

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

void setup() {
  Serial.begin(9600);

  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.fillScreen(ST77XX_BLACK);

  // Initialize ADC functionality and switch input
  adcInit();
  DDRD &= ~(1 << SW);
  PORTD |= (1 << SW);

  // Display Welcome Screen
  tft.setTextWrap(true);
  tft.setRotation(1); // Rotate view 90 degrees
  // Display_Menu();

  brushInit(tft);
}

void loop() {
  // Change the brush color if the joystick switch is pressed
  if(!(PIND & (1 << SW))) {
    colorChange(tft);
  }
  
  // Obtaining analog values and changing range to -512 to +512
  xVal = readAnalogInput(VRx) - 511;
  yVal = readAnalogInput(VRy) - 511;
  brushMove(tft, xVal, yVal);

  // Draw a square in the current brush position only if the joystick has changed the brush position
  if(xVal < -20 || xVal > 20 || yVal < -20 || yVal > 20) {
    sketch(tft);
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
