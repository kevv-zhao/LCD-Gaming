/*--------------------------------------------------------------------
Name:   Kevin Zhao
Date:   2022, January 20
File:   etch_a_sketch.h

Purp: 

Doc:  
--------------------------------------------------------------------*/

int16_t paddlePos[2];
int8_t paddleSpdMax = 20;
int8_t paddleWidth = 4;
int8_t paddleLength = 24;

int16_t ballPos[2]; // {X,Y} position of the ball
int ballSpeeds[2];  // {X,Y} speeds of the ball
int ballSpdMax = 7;

void paddleInit(Adafruit_ST7735 tft) {
    // Paddle Setup
    paddlePos[0] = tft.height()/2 - paddleLength/2; paddlePos[1] = tft.height()/2 - paddleLength/2;
    tft.fillRect(4, paddlePos[0], paddleWidth, paddleLength, ST7735_WHITE);
}

void ballInit(Adafruit_ST7735 tft) {
  ballPos[0] = tft.width()/2; ballPos[1] = tft.height()/2;
  tft.fillCircle(ballPos[0], ballPos[1], 3, ST7735_WHITE);
  ballSpeeds[0] = random(2,ballSpdMax);
  ballSpeeds[1] = random(1,ballSpdMax);
}

void paddleMove(Adafruit_ST7735 tft, int xVal, int yVal) {
    // Paddle movement
    if((paddlePos[0] + (yVal*paddleSpdMax/511) < 0 && yVal < -20) || 
    (paddlePos[0] + (yVal*paddleSpdMax/511) > tft.height()-paddleLength && yVal > 20)) {
        // Edge cases for when the paddle nears the edge of the screen and is stopped
        tft.fillRect(4, paddlePos[0], paddleWidth, paddleLength, ST7735_BLACK);
        if(yVal*paddleSpdMax/511 < 0) {
            paddlePos[0] = 0;
        } else {
            paddlePos[0] = tft.height()-paddleLength;
        }
        tft.fillRect(4, paddlePos[0], paddleWidth, paddleLength, ST7735_WHITE);

    } else if((paddlePos[0] >= 0 && yVal < -20) || (paddlePos[0] <= tft.height()-paddleLength && yVal > 20)) {
        // General paddle movement, non-edge cases
        tft.fillRect(4, paddlePos[0], paddleWidth, paddleLength, ST7735_BLACK);
        paddlePos[0] = paddlePos[0] + (yVal*paddleSpdMax/511);
        tft.fillRect(4, paddlePos[0], paddleWidth, paddleLength, ST7735_WHITE);
    }
}

void ballMove(Adafruit_ST7735 tft) {
    // Moving the ball
    tft.fillCircle(ballPos[0], ballPos[1], 3, ST7735_BLACK);
    ballPos[0] = ballPos[0] + ballSpeeds[0];
    ballPos[1] = ballPos[1] + ballSpeeds[1];
    tft.fillCircle(ballPos[0], ballPos[1], 3, ST7735_WHITE);
}

void ballCheck(Adafruit_ST7735 tft, int yVal) {
    // Checking on the conddition of the ball for bouncing or scoring a point
    if(ballPos[0] > tft.width()-4) {
        // This will be the condition for the  player to score a point
        ballSpeeds[0] = -ballSpeeds[0]; // CHANGE TO SCORING A POINT AND REPAWNING THE BALL

    } else if (ballPos[0] < 0) {
        // Respawns the ball if it goes past the paddle
        delay(500);
        tft.fillCircle(ballPos[0], ballPos[1], 3, ST7735_BLACK);
        ballInit(tft);

    } else if(ballPos[1] < 4) {
        // Bounces the ball off the top of the screen
        ballSpeeds[1] = abs(ballSpeeds[1]);

    } else if(ballPos[1] > tft.height()-4) {
        // Bounces the ball off the bottome of the screen
        ballSpeeds[1] = -abs(ballSpeeds[1]);

    } else if(ballPos[0] > paddleWidth+4 && ballPos[0] < paddleWidth+4+4 && 
    paddlePos[0]-4 <= ballPos[1] && paddlePos[0]+paddleLength+4 >= ballPos[1]) {
        // Bounces the ball off the paddle
        ballSpeeds[0] = random(2, ballSpdMax);
        ballSpeeds[1] = ballSpeeds[1] + yVal*ballSpdMax/511;
    }
}