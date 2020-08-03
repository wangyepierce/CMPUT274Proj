# CMPUT274 Final Project

XIAOJIE XING

YE WANG

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

Accessories:
* Arduino mega 2560 board with usb cable
* TFT display
* Many jumper wires
* 2 Joy Sticks

WIRING INSTRUCTIONS:

for display:

Board Pin     <---> 	Arduino Pin

===========================

GND                 	GND

Vin       		5V

3Vo                  	NOT CONNECTED

CLK           	 	52

MISO            	50

MOSI            	51

CS              	10

D/C             	9

RST             	NOT CONNECTED

Lite            	NOT CONNECTED

Y+              	A2 (analog pin)

X+              	4  (digital pin)

Y-              	5  (digital pin)

X-              	A3 (analog pin)

IM0 - IM3       	NOT CONNECTED (they expect a 3.3v signal, DON'T CONNECT!)

CCS             	6

CD              	NOT CONNECTED


for joy stick 1 (Player 1):

Arduino Analog pin A1 <--> joy stick pin VRx

Arduino Analog pin A0 <--> joy stick pin VRy

Arduino GND <--> joy stick GND

Arduino 5V <--> joy stick 5V

for joy stick 2 (Player 1):

Arduino Analog pin A5 <--> joy stick pin VRx

Arduino Analog pin A4 <--> joy stick pin VRy

Arduino GND <--> joy stick GND

Arduino 5V <--> joy stick 5V

INSTRUCTION TO RUN THE CODE:
1. Load all files into one single folder in Linux VM
2. Connect Arduino mega 2560 to VM use USB cable
3. Check if wiring is done correctly
4. Direct to project file in terminal
5. Type command 'make upload' in terminal
