#ifndef _COMMONDEFS_H
#define _COMMONDEFS_H

#define TFT_DC 9
#define TFT_CS 10
#define SD_CS 6

// Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0
#define WHITE    0xFFFF

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM  5  // can be a digital pin
#define XP  4  // can be a digital pin

// calibration data for the touch screen, obtained from documentation
// the minimum/maximum possible readings from the touch poextern int
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

// width/height of the display when rotated horizontally
#define TFT_WIDTH 320
#define TFT_HEIGHT 240

// thresholds to determine if there was a touch
#define MINPRESSURE   10
#define MAXPRESSURE 1000

#define DISPLAY_WIDTH  320
#define DISPLAY_HEIGHT 240

#define JOY_VERT_1  A1 // should connect A1 to pin VRx
#define JOY_HORIZ_1 A0 // should connect A0 to pin VRy

#define JOY_VERT_2  A5 // should connect A5 to pin VRx
#define JOY_HORIZ_2 A4 // should connect A4 to pin VRy

#define JOY_CENTER   512 // joy stick  center value
#define JOY_DEADZONE 64	// joy stick freeze zone
#define JOY_SPEED 194

#define BALL_R 4	// radius of ball

#define PADDLE_WIDTH 5
#define PADDLE_LENGTH 32

#define MAX_SCORE 7

#endif
