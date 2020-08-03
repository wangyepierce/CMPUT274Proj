#ifndef _GAME_FUNCTIONS_
#define _GAME_FUNCTIONS_

// after the ball hit the boundaries of the screen,
// it will create a random speed
void randomSpeed();

// after the ball hit the paddles, it will accelerate and form a random direction
void randomHitSpeed();

// when the paddles move, need to redraw the paddles and cover the previous paddles
void redrawPaddle(int x, int y, int oldx, int oldy);

// if the ball hit the gates, the score will increase
void checkScore();

// check all the hits situation
void checkHit();

// determine loaction of the ball and rebounce
void ballLocation();

// reset game when some one get the score
void resetGame();

// create a score menu
void scoreMenu();

// when someone get 7, show the result
void checkWin();

// how the AI works
void AI();

// make the touch screen available
void checkTouch();

// the design of start menu
void checkStart();

// when the p2 win
void p2win();

// when the p1 win
void p1win();

// redraw the ball when the ball moves and cover the previous ball
void drawBall(int ball_x, int ball_y);

// the PVP mode
void PlayerVSplayer(int ball_x, int ball_y);

// the PVC mode
void PlayerVScomputer();

#endif
