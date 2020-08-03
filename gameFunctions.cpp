#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#include "gameFunctions.h"
#include "commonDefs.h"

extern Adafruit_ILI9341 tft;
extern TouchScreen ts;

extern int ball_x;
extern int ball_y;

// x+y <=6
extern int ball_x_speed; // X(1~6)
extern int ball_y_speed; // Y(0~5)

// initialize the direction of the ball
extern int ball_x_dir;
extern int ball_y_dir;

extern int p1score;// player 1 score
extern int p2score;// player 2 score
extern int oldP1Score;
extern int oldP2Score;

// x y postion of player 1
extern int p1_x;
extern int p1_y;
// x y postion of player 2
extern int p2_x;
extern int p2_y;

extern int gameMode;
extern bool PVP;

// after the ball hit the boundaries of the screen,
// it will create a random speed
void randomSpeed(){
	ball_x_speed =random(1,5);
	ball_y_speed =random(max(5-ball_x_speed,2));
}

// after the ball hit the paddles, it will accelerate and form a random direction
void randomHitSpeed(){
	ball_x_speed = random(3,5);
	ball_y_speed = random(max(5-ball_x_speed,2));
}

// when the paddles move, need to redraw the paddles and cover the previous paddles
void redrawPaddle(int x, int y, int oldx, int oldy){
	tft.fillRect(oldx,oldy,PADDLE_WIDTH,PADDLE_LENGTH,BLACK);
	tft.fillRect(x,y,PADDLE_WIDTH,PADDLE_LENGTH,WHITE);
}

// if the ball hit the gates, the score will increase
void checkScore(){
	if(ball_x<=5){
		if(ball_y>= 99 && ball_y <= 161){
			p2score ++;
		}
	}

	if(ball_x>=315){
		if(ball_y>= 99 && ball_y <= 161){
			p1score ++;
		}
	}
}

// check all the hits situation
void checkHit(){
	// when the ball goes left
	if(ball_x_dir == -1){
		// when the ball hit the right half of the paddle 1
		if(ball_x <= p1_x+9 && ball_x > p1_x-1){
			if((ball_y >=p1_y)&&(ball_y<=p1_y + PADDLE_LENGTH)){
				ball_x = p1_x+9;

				ball_x_dir = -ball_x_dir;
				ball_y_dir = -ball_y_dir;

				randomHitSpeed();
			}
		}
		// when the ball hit the left half of the paddle
		if(ball_x >= p1_x -4 && ball_x < p1_x +5){
			if((ball_y >=p1_y)&&(ball_y<=p1_y + PADDLE_LENGTH)){
				randomHitSpeed();
			}
		}

		// when the ball hit the right half of the paddle 2
		if(ball_x <= p2_x+9 && ball_x > p2_x-1){
			if((ball_y >=p2_y)&&(ball_y<=p2_y + PADDLE_LENGTH)){
				ball_x = p2_x+9;

				ball_x_dir = -ball_x_dir;
				ball_y_dir = -ball_y_dir;

				randomHitSpeed();
			}
		}
		// when the ball hit the left half of the paddle 2
		if(ball_x >= p2_x -4 && ball_x < p2_x +5){
			if((ball_y >=p2_y)&&(ball_y<=p2_y + PADDLE_LENGTH)){
				ball_x_speed = random(3,5);
				ball_y_speed = random(max(5-ball_x_speed,2));
			}
		}
	}

	// when the ball goes right
	if(ball_x_dir ==1 ){
		// when the ball hit the left half of the paddle 1
		if(ball_x >= p1_x -4 && ball_x < p1_x +5){
			if((ball_y >=p1_y)&&(ball_y<=p1_y + PADDLE_LENGTH)){
				ball_x = p1_x-4;

				ball_x_dir = -ball_x_dir;
				ball_y_dir = -ball_y_dir;

				randomHitSpeed();
			}
		}
		// when the ball hit the right half of the paddle 1
		if(ball_x >= p1_x +5 && ball_x < p1_x+9){
			if((ball_y >=p1_y)&&(ball_y<=p1_y + PADDLE_LENGTH)){
				randomHitSpeed();
			}
		}

		// when the ball hit the left half of the paddle 2
		if(ball_x >= p2_x -4 && ball_x < p2_x +5){
			if((ball_y >=p2_y)&&(ball_y<=p2_y + PADDLE_LENGTH)){
				ball_x = p2_x-4;

				ball_x_dir = -ball_x_dir;
				ball_y_dir = -ball_y_dir;

				randomHitSpeed();
			}
		}
		// when the ball hit the right half of the paddle 2
		if(ball_x >= p2_x +5 && ball_x < p2_x+9){
			if((ball_y >=p2_y)&&(ball_y<=p2_y + PADDLE_LENGTH)){
				randomHitSpeed();
			}
		}
	}
}

// reset game when some one get the score
void resetGame(){

	delay(100);

	tft.fillRect(0,21,320,219,BLACK);

	// get the ball back to the center of the screen
	ball_x = DISPLAY_WIDTH/2;
	ball_y = DISPLAY_HEIGHT/2;
	tft.fillCircle(ball_x,ball_y,BALL_R,CYAN);

	// get the paddles back to the initial position
	redrawPaddle(20, 114, p1_x, p1_y);
	redrawPaddle(299,114, p2_x, p2_y);
	// x y postion of player 1
	p1_x = 20;
	p1_y = 114;
	// x y postion of player 2
	p2_x = 299;
	p2_y = 114;

	// redraw the gates
	tft.drawLine(0,95,0,165,GREEN);
	tft.drawLine(319,95,319,165,GREEN);

	delay(1000);
}

// create a score menu
void scoreMenu(){

	checkScore();

	// design of the score menu
	tft.drawLine(0,20,320,20,WHITE);

	tft.drawLine(0,95,0,165,GREEN);
	tft.drawLine(319,95,319,165,GREEN);

	// p1score = constrain(p1score,0,MAX_SCORE);
	// p2score = constrain(p2score,0,MAX_SCORE);


	tft.setCursor(5,2);
	tft.setTextColor(WHITE);
	tft.setTextWrap(false);

	// print the p1 score
	tft.setTextSize(2);
	if(oldP1Score != p1score){
		tft.fillRect(0,0,19,19,BLACK);
		tft.print(p1score);
		oldP1Score = p1score;
		resetGame();
	}

	// print the p2 score
	tft.setCursor(305,2);
	if(oldP2Score != p2score){
		tft.fillRect(300,0,19,19,BLACK);
		tft.print(p2score);
		oldP2Score = p2score;
		resetGame();
	}

	// print "SCORE" in the middle of the score menu
	tft.setCursor(130,2);
	tft.print("SCORE");
}

// determine loaction of the ball and rebounce
void ballLocation(){
	// create a constrain for the ball
	ball_x = constrain(ball_x,5,315);
	ball_y = constrain(ball_y,25,235);

	//make the ball to move and change direction
	ball_x = ball_x+ball_x_speed*ball_x_dir;
	ball_y = ball_y+ball_y_speed*ball_y_dir;

	// when the ball hit the right boundary
	if(ball_x >= 315){
		ball_x = 315;
		ball_x_dir *=(-1);
		randomSpeed();
	}
	// when the ball hit the left boundary
	else if(ball_x <= 5){
		ball_x=5;
		ball_x_dir *=(-1);
		randomSpeed();
	}
	// when the ball hit the bottom boundary
	if(ball_y >= 235 ){
		ball_y = 235;
		ball_y_dir *=(-1);
		randomSpeed();
	}
	// when the ball hit the top boundary
	else if(ball_y <= 25){
		ball_y = 25;
		ball_y_dir *=(-1);
		randomSpeed();
	}
}

// redraw the ball when the ball moves and cover the previous ball
void drawBall(int ball_x, int ball_y){

	ballLocation();
	checkHit();


if(ball_y_dir>0 and ball_x_dir>0){
	tft.fillCircle(ball_x-1,ball_y-1,BALL_R+5,BLACK);
}
else if(ball_y_dir<0 and ball_x_dir<0){
	tft.fillCircle(ball_x+1,ball_y+1,BALL_R+5,BLACK);
}
else if(ball_y_dir>0 and ball_x_dir<0){
	tft.fillCircle(ball_x+1,ball_y-1,BALL_R+5,BLACK);
}
else if(ball_y_dir<0 and ball_x_dir>0){
	tft.fillCircle(ball_x-1,ball_y+1,BALL_R+5,BLACK);
}
	tft.fillCircle(ball_x,ball_y,BALL_R,CYAN);

	scoreMenu();

}

// when someone get 7, show the result
void checkWin(){
	if(p1score == 7){
		gameMode =2;
		tft.fillScreen(BLACK);
	}
	if(p2score ==7){
		gameMode =3;
		tft.fillScreen(BLACK);
	}
}

// when the p1 win
void p1win(){
	String P2;
	if(PVP){
		P2 = "PLAYER 2"; // PVP mode
	}
	else{
		P2 = "COMPUTER"; // PVC mode
	}

	// the design of the result board
	tft.fillRect(0,0,159,240,WHITE);
	tft.fillRect(159,0,159,240,BLACK);

	tft.setTextSize(3);
	tft.setTextWrap(false);
	tft.setTextColor(BLACK);

	tft.setCursor(15,110);
	tft.print("VICTORY!");
	tft.setCursor(15,50);
	tft.print("PLAYER 1");
	tft.setCursor(70,160);
	tft.print(p1score);
	p1score =0;

	tft.setTextColor(WHITE);
	tft.setCursor(174,110);
	tft.print("DEFEAT..");
	tft.setCursor(174,50);
	tft.print(P2);
	tft.setCursor(229,160);
	tft.print(p2score);
	p2score =0;

	gameMode =0;
	delay(3000);
	tft.fillScreen(BLACK);
}

// when the p2 win
void p2win(){
	String P2;
	if(PVP){
		P2 = "PLAYER 2"; // PVP  mode
	}
	else{
		P2 = "COMPUTER"; // PVC mode
	}

	// the design of result board
	tft.fillRect(0,0,159,240,BLACK);
	tft.fillRect(159,0,159,240,WHITE);

	tft.setTextSize(3);
	tft.setTextWrap(false);
	tft.setTextColor(WHITE);

	tft.setCursor(15,110);
	tft.print("DEFEAT..");
	tft.setCursor(15,50);
	tft.print("PLAYER 1");
	tft.setCursor(70,160);
	tft.print(p1score);
	p1score =0;

	tft.setTextColor(BLACK);
	tft.setCursor(174,110);
	tft.print("VICTORY!");
	tft.setCursor(174,50);
	tft.print(P2);
	tft.setCursor(229,160);
	tft.print(p2score);
	p2score =0;

	gameMode = 0;
	delay(3000);
	tft.fillScreen(BLACK);
}

// the design of start menu
void checkStart(){
	tft.drawRoundRect(40,20,240,95,25,WHITE);
	tft.drawRoundRect(40,125,240,95,25,WHITE);

	tft.setCursor(75,35);
	tft.setTextColor(WHITE);
	tft.setTextWrap(false);

	tft.setTextSize(3);
	tft.print("Air Hockey");
	tft.setCursor(75,140);
	tft.print("Air Hockey");

	tft.setCursor(68,75);
	tft.setTextSize(2);
	tft.print("Player VS Player");
	tft.setCursor(55,180);
	tft.print("Player VS Computer");
}

// make the touch screen available
void checkTouch() {

	checkStart();

	TSPoint touch = ts.getPoint();

	if (touch.z < MINPRESSURE || touch.z > MAXPRESSURE) {
		// no touch, just quit
		return;
	}

	// get the y coordinate of where the display was touched
	// remember the x-coordinate of touch is really our y-coordinate
	// on the display
	int touchY = map(touch.x, TS_MINX, TS_MAXX, 0, TFT_HEIGHT - 1);

	// need to invert the x-axis, so reverse the
	// range of the display coordinates
	int touchX = map(touch.y, TS_MINY, TS_MAXY, TFT_WIDTH - 1, 0);

	Serial.println(touchX);
	Serial.println(touchY);

	// when u touch the first round rectangle, go to PVP mode
	if(touchX>40 && touchX<280){
		if(touchY>10 && touchY < 115){
			tft.fillRoundRect(40,20,240,95,25,WHITE);
			tft.setCursor(75,35);
			tft.setTextColor(BLACK);
			tft.setTextWrap(false);

			tft.setTextSize(3);
			tft.print("Air Hockey");

			tft.setCursor(85,75);
			tft.setTextSize(2);
			tft.print("Ready to Play");

			PVP =1;
			gameMode =1;

			delay(1000);
		}

		// when u touch the second round rectangle, go to the PVC mode
		if (touchY > 125 && touchY < 230){
			tft.fillRoundRect(40,125,240,95,25,WHITE);
			tft.setCursor(75,140);
			tft.setTextColor(BLACK);
			tft.setTextColor(false);

			tft.setTextSize(3);
			tft.print("Air Hockey");

			tft.setCursor(85,175);
			tft.setTextSize(2);
			tft.print("Ready to Play");

			PVP = 0;
			gameMode = 4;

			delay(1000);
		}

	}
}

// the AI for player vs computer mode
void AI(){
	// when the ball stucks near the boundaries, freeze the paddle
	if (ball_x > 300 && ball_y < 110) {
		p2_y = p2_y;
	}
	if (ball_x > 300 && ball_y > 110) {
		p2_y = p2_y;
	}

	// control the up and down speed of the paddle
	if (ball_y > p2_y + 16){
		p2_y += round(sqrt(pow(ball_y_speed,2)+pow(ball_x_speed,2)));
	}
	else if (ball_y < p2_y + 8){
		p2_y -= round(sqrt(pow(ball_y_speed,2)+pow(ball_x_speed,2)));
	}

	// control the right and left speed of the paddle
	if (ball_x < 120){
		p2_x -= 1;
	}
	else if (ball_x > 120){
		p2_x += 2;
	}
}

// the PVP mode
void PlayerVSplayer(int ball_x, int ball_y){
	//player 1 joystick
	int xVal_1 = analogRead(JOY_HORIZ_1);
  int yVal_1 = analogRead(JOY_VERT_1);

	//player 2 joy stick
	int xVal_2 = analogRead(JOY_HORIZ_2);
	int yVal_2 = analogRead(JOY_VERT_2);

	int oldxVal_1 = p1_x;
	int oldyVal_1 = p1_y;

	int oldxVal_2 = p2_x;
	int oldyVal_2 = p2_y;

	// the speed of paddles controled by joysticks
	p1_x += (JOY_CENTER - xVal_1) / JOY_SPEED;
	p1_y +=	(yVal_1 - JOY_CENTER) / (JOY_SPEED*2/3);

	p2_x += (JOY_CENTER - xVal_2) / JOY_SPEED;
	p2_y +=	(yVal_2 - JOY_CENTER) / (JOY_SPEED*2/3);

	// create constrains of paddles, to make sure that they can't go across
	// the middle of the screen and the gates
	p1_x = constrain(p1_x,20,136);
	p1_y = constrain(p1_y,21,207);

	p2_x = constrain(p2_x,180,295);
	p2_y = constrain(p2_y,21,207);

	// make sure the paddles can't go over the constrains
	if(p1_x <= 20){
		p1_x = 20;
	}
	else if(p1_x >= 136){
		p1_x = 136;
	}

	if(p1_y <= 21){
		p1_y = 21;
	}
	else if(p1_y >= 207){
		p1_y = 207;
	}

	if(p2_x <= 180){
		p2_x = 180;
	}
	else if(p2_x >= 295){
		p2_x = 295;
	}

	if(p2_y <= 21){
		p2_y = 21;
	}
	else if(p2_y >= 207){
		p2_y = 207;
	}
	redrawPaddle(p1_x,p1_y,oldxVal_1,oldyVal_1);
	redrawPaddle(p2_x,p2_y,oldxVal_2,oldyVal_2);

	drawBall(ball_x,ball_y);

	checkWin();

}

// the PVC mode
void PlayerVScomputer(){
	//player 1 joystick
	int xVal_1 = analogRead(JOY_HORIZ_1);
  int yVal_1 = analogRead(JOY_VERT_1);

	int oldxVal_1 = p1_x;
	int oldyVal_1 = p1_y;

	int oldxVal_2 = p2_x;
	int oldyVal_2 = p2_y;

	// the speed of paddle controled by the joystick
	p1_x += (JOY_CENTER - xVal_1) / JOY_SPEED;
	p1_y +=	(yVal_1 - JOY_CENTER) / (JOY_SPEED*2/3);

	AI();

	// create constrains for each paddle
	p1_x = constrain(p1_x,20,136);
	p1_y = constrain(p1_y,21,207);

	p2_x = constrain(p2_x,180,295);
	p2_y = constrain(p2_y,21,207);

	// make sure the paddles dont cross over the constrains
	if(p1_x <= 20){
		p1_x = 20;
	}
	else if(p1_x >= 136){
		p1_x = 136;
	}

	if(p1_y <= 21){
		p1_y = 21;
	}
	else if(p1_y >= 207){
		p1_y = 207;
	}

	if(p2_x <= 180){
		p2_x = 180;
	}
	else if(p2_x >= 295){
		p2_x = 295;
	}

	if(p2_y <= 21){
		p2_y = 21;
	}
	else if(p2_y >= 207){
		p2_y = 207;
	}

	redrawPaddle(p1_x,p1_y,oldxVal_1,oldyVal_1);
	redrawPaddle(p2_x,p2_y,oldxVal_2,oldyVal_2);

	drawBall(ball_x,ball_y);

	checkWin();
}
