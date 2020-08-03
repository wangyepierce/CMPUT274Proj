/*
XIAOJIE XING
ID:

YE WANG
ID:

Final Project: Air Hockey

Acknowledgement:
* the checkTouch function refers to the sample code from google drive
* all of other codes are implemented by ourselves

Description:
* This program is an Air Hockey game that runs on Arduino, with 5 different modes,
which are mode 0,1,2,3,4.

* This program will start with mode 0, which is just a start board. Players can
choose PVP or PVC mode by touching the screen.

* If the player chooses PVP mode, the program will go to mode 1. It needs two
players to control two different joysticks. Each joystick can control each paddle
to move right and left, forwards and backwards. And the ball will accelerate when
the ball hits the paddles and the direction will depend on the the side that hits
the ball. And the ball will bounce when it hits the walls. When the entire ball
hits the gate completely, the player will get one point and the game will end when
one player's score reach seven. The program will go to the mode 2 or 3 depends on
which player wins.

* If the player chooses PVC mode, the program will go the mode 4. It only needs
one player to control one joystick to against computer. Other rules and process
will be exactly same as PVP mode.

* After showing up the result board which is mode 2 or 3, the program will go
back to mode 0 which can make the player to choose different game mode.

* joystick connect to pin A1 and A0 will only be used as player 1, A5 A4 will be player 2;
	in player vs computer mode, game AI will replace player 2, only player 1 can move joystick.
*/

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#include "gameFunctions.h"
#include "commonDefs.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

//initialize the position of the ball
int ball_x = DISPLAY_WIDTH/2;
int ball_y = DISPLAY_HEIGHT/2;

// x+y <=6
int ball_x_speed = random(2,5); // X(1~6)
int ball_y_speed = random(max(5-ball_x_speed,1)); // Y(0~5)

// initialize the direction of the ball
int ball_x_dir = 1;
int ball_y_dir = 1;

int p1score = 0;// player 1 score
int p2score = 0;// player 2 score
int oldP1Score = -1;
int oldP2Score = -1;

// x y postion of player 1
int p1_x = 20;
int p1_y = 114;
// x y postion of player 2
int p2_x = 299;
int p2_y = 114;

int gameMode =0;

bool PVP = 1;

void setup(){
	init();
	Serial.begin(9600);

	tft.begin();

	tft.setRotation(3);

	tft.fillScreen(ILI9341_BLACK);

	// genernate random seed for random numbers
	// analog pin A9 is an unused pin
	randomSeed(min((uint8_t)analogRead(A9)>>5,7));
}

int main(){
	setup();
	int flash =1;
	int noflash =0;

	while(true){
		// start menu
		if(gameMode == 0){
			noflash = 0;
			checkTouch();
		}
		// PVP mode
		else if (gameMode == 1){
			PlayerVSplayer(ball_x,ball_y);
		}
		// player 1 wins
		else if(gameMode ==2){
			if(flash != noflash){
				p1win();
				noflash =1;
			}
		}
		// player 2 wins
		else if(gameMode ==3){
			if(flash!=noflash){
				p2win();
				noflash = 1;
			}
		}
		// PVC mode
		else if (gameMode == 4){
			PlayerVScomputer();
		}
	}

	Serial.end();
	return 0;
}
