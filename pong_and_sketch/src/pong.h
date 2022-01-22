/*--------------------------------------------------------------------
Name:   Kevin Zhao
Date:   2022, January 20
File:   etch_a_sketch.h

Purp: 

Doc:  
--------------------------------------------------------------------*/

int16_t paddlePos[2];
int8_t paddleSpeed = 20;
int8_t paddleWidth = 4;
int8_t paddleLength = 24;

void paddleInit(Adafruit_ST7735 tft) {
    // Paddle Setup
    paddlePos[0] = tft.height()/2 - paddleLength/2; paddlePos[1] = tft.height()/2 - paddleLength/2;
    tft.fillRect(4, paddlePos[0], paddleWidth, paddleLength, ST7735_WHITE);
}

void paddleMove(Adafruit_ST7735 tft, int xVal, int yVal) {
    // Paddle movement
    if((paddlePos[0] + (yVal*paddleSpeed/511) < 0 && yVal < -20) || 
    (paddlePos[0] + (yVal*paddleSpeed/511) > tft.height()-paddleLength && yVal > 20)) {
        // Edge cases for when the paddle nears the edge of the screen and is stopped
        tft.fillRect(4, paddlePos[0], paddleWidth, paddleLength, ST7735_BLACK);
        if(yVal*paddleSpeed/511 < 0) {
            paddlePos[0] = 0;
        } else {
            paddlePos[0] = tft.height()-paddleLength;
        }
        tft.fillRect(4, paddlePos[0], paddleWidth, paddleLength, ST7735_WHITE);

    } else if((paddlePos[0] >= 0 && yVal < -20) || (paddlePos[0] <= tft.height()-paddleLength && yVal > 20)) {
        // General paddle movement, non-edge cases
        tft.fillRect(4, paddlePos[0], paddleWidth, paddleLength, ST7735_BLACK);
        paddlePos[0] = paddlePos[0] + (yVal*paddleSpeed/511);
        tft.fillRect(4, paddlePos[0], paddleWidth, paddleLength, ST7735_WHITE);
    }
}

void ballMove(Adafruit_ST7735 tft) {
    
}