/*--------------------------------------------------------------------
Name:   Kevin Zhao
Date:   2022, January 20
File:   etch_a_sketch.h

Purp: 

Doc:  
--------------------------------------------------------------------*/

// Etch-a-Sketch Cursor Position and Color Pallet
int16_t brushPos[2];
int16_t brushPrev[2];
uint16_t pallet[] = {ST77XX_RED, ST77XX_ORANGE, ST77XX_YELLOW, ST77XX_GREEN, 
ST7735_CYAN, ST7735_BLUE, ST7735_MAGENTA, ST7735_WHITE, ST77XX_BLACK};
int color = 0;

/*
 * Fill in the previous cursor position with a single color square and display a 
 * partially bordered square in the current cursor position.
 */
void sketch(Adafruit_ST7735 tft) {
    tft.fillRect(brushPrev[0], brushPrev[1], 4, 4, pallet[color]);
    if(color != 8) {
        tft.fillRect(brushPos[0], brushPos[1], 4, 4, ST7735_BLACK);
        tft.fillRect(brushPos[0], brushPos[1], 3, 3, pallet[color]);
    } else {
        tft.fillRect(brushPos[0], brushPos[1], 4, 4, ST7735_WHITE);
        tft.fillRect(brushPos[0], brushPos[1], 3, 3, pallet[color]);
    }
}

/*
 * Initializing the brush position based off the current dimensions of the screen.
 */
void brushInit(Adafruit_ST7735 tft) {
  brushPos[0] = tft.width()/2 - 2; brushPos[1] = tft.height()/2 - 2;
  brushPrev[0] = brushPos[0]; brushPrev[1] = brushPos[1];
  sketch(tft);
}

/*
 * Increment the cursor position based off a joystick input.
 */
void brushMove(Adafruit_ST7735 tft, int xVal, int yVal) {
    brushPrev[0] = brushPos[0]; brushPrev[1] = brushPos[1];
    if((brushPos[0] > 0 && xVal < -20) || (brushPos[0] <= tft.width()-4 && xVal > 20)) {
        brushPos[0] = brushPos[0] + (xVal*3/511);
    }
    if((brushPos[1] >= 0 && yVal < -20) || (brushPos[1] <= tft.height()-4 && yVal > 20)) {
        brushPos[1] = brushPos[1] + (yVal*3/511);
    }
}

void colorChange(Adafruit_ST7735 tft) {
    color = (color+1) % 9;
    sketch(tft);
}