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
#include "pong.h"

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
int16_t ballPos[2]; // Ball's {X,Y} position
int trajRand[2];
int randMax = 4;

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

  paddleInit(tft);
  ballPos[0] = tft.width()/2; ballPos[1] = tft.height()/2;
  tft.fillCircle(ballPos[0], ballPos[1], 3, ST7735_WHITE);
  trajRand[0] = random(-randMax,randMax);
  trajRand[1] = random(-randMax,randMax);
}

void loop() {
  // Obtaining analog values and changing range to -512 to +512
  xVal = readAnalogInput(VRx) - 511;
  yVal = readAnalogInput(VRy) - 511;

  paddleMove(tft, xVal, yVal);

  // Moving the ball
  tft.fillCircle(ballPos[0], ballPos[1], 3, ST7735_BLACK);
  ballPos[0] = ballPos[0] + trajRand[0];
  ballPos[1] = ballPos[1] + trajRand[1];
  tft.fillCircle(ballPos[0], ballPos[1], 3, ST7735_WHITE);

  // Checking on the conddition of the ball for bouncing or scoring a point
  if(ballPos[0] > tft.width()-4) {
    // This will be the condition for the second player to score a point
    trajRand[0] = -trajRand[0]; // CHANGE TO SCORING A POINT AND REPAWNING THE BALL

  } else if(ballPos[1] > tft.height()-4 || ballPos[1] < 4) {
    // Bounces the ball off the horizontal walls
    trajRand[1] = -trajRand[1];
    
  } else if(ballPos[0] > paddleWidth+4 && ballPos[0] < paddleWidth+4 && 
  paddlePos[0]+4 <= ballPos[1] && paddlePos[0]+paddleLength+4 >= ballPos[1]) {
    // Bounces the ball off the paddle
    trajRand[0] = -trajRand[0];
  }
  
  delay(50);
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
