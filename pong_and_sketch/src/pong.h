/*--------------------------------------------------------------------
Name:   Kevin Zhao
Date:   2022, January 20
File:   etch_a_sketch.h

Purp: 

Doc:  
--------------------------------------------------------------------*/

int16_t paddlePos[2];
int8_t paddleSpeed = 20;

void paddleInit(Adafruit_ST7735 tft) {
    // Paddle Setup
    paddlePos[0] = tft.height()/2 - 12; paddlePos[1] = tft.height()/2 - 12;
    tft.fillRect(4, paddlePos[0], 4, 24, ST7735_WHITE);
}

void paddleMove(Adafruit_ST7735 tft, int xVal, int yVal) {
    // Paddle movement
    if((paddlePos[0] + (yVal*paddleSpeed/511) < 0 && yVal < -20) || 
    (paddlePos[0] + (yVal*paddleSpeed/511) > tft.height()-24 && yVal > 20)) {
        // Edge cases for when the paddle nears the edge of the screen and is stopped
        tft.fillRect(4, paddlePos[0], 4, 24, ST7735_BLACK);
        if(yVal*paddleSpeed/511 < 0) {
        paddlePos[0] = 0;
        } else {
        paddlePos[0] = tft.height()-24;
        }
        tft.fillRect(4, paddlePos[0], 4, 24, ST7735_WHITE);

    } else if((paddlePos[0] >= 0 && yVal < -20) || (paddlePos[0] <= tft.height()-24 && yVal > 20)) {
        // General paddle movement, non-edge cases
        tft.fillRect(4, paddlePos[0], 4, 24, ST7735_BLACK);
        paddlePos[0] = paddlePos[0] + (yVal*paddleSpeed/511);
        tft.fillRect(4, paddlePos[0], 4, 24, ST7735_WHITE);
    }
}

void ballMove(Adafruit_ST7735 tft) {
    
}