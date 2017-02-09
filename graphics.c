#include <stdio.h>
#include "DrawChar.h"
#include "Gps.h"
#include "Colours.h"
#include "graphics.h"

/**********************************************************************
* This function writes a single pixel to the x,y coords specified in the specified colour
* Note colour is a palette number (0-255) not a 24 bit RGB value
**********************************************************************/
void WriteAPixel (int x, int y, int Colour)
{
	WAIT_FOR_GRAPHICS;			// is graphics ready for new command

	GraphicsX1Reg = x;			// write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsColourReg = Colour;		// set pixel colour with a palette number
	GraphicsCommandReg = PutAPixel;		// give graphics a "write pixel" command
}

void WriteHLine (int x1, int x2, int y, int Colour)
{
	WAIT_FOR_GRAPHICS;			// is graphics ready for new command

	GraphicsX1Reg = x1;			// write coords to x1, y1
	GraphicsX2Reg = x2;
	GraphicsY1Reg = y;

	GraphicsColourReg = Colour;		// set pixel colour with a palette number
	GraphicsCommandReg = DrawHLine;		// give graphics a "draw Horizontal Line" command
}

/*****************************************************************************************
* This function read a single pixel from x,y coords specified and returns its colour
* Note returned colour is a palette number (0-255) not a 24 bit RGB value
******************************************************************************************/
int ReadAPixel (int x, int y)
{
	WAIT_FOR_GRAPHICS;			// is graphics ready for new command

	GraphicsX1Reg = x;			// write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsCommandReg = GetAPixel;		// give graphics a "get pixel" command

	WAIT_FOR_GRAPHICS;			// is graphics done reading pixel
	return (int)(GraphicsColourReg) ;		// return the palette number (colour)
}

/****************************************************************************************************
** subroutine to program a hardware (graphics chip) palette number with an RGB value
** e.g. ProgramPalette(RED, 0x00FF0000) ;
****************************************************************************************************/

void ProgramPalette(int PaletteNumber, int RGB)
{
	WAIT_FOR_GRAPHICS;
	GraphicsColourReg = PaletteNumber;
	GraphicsX1Reg = RGB >> 16   ;          // program red value in ls.8 bit of X1 reg
	GraphicsY1Reg = RGB ;                	 // program green and blue into 16 bit of Y1 reg
	GraphicsCommandReg = ProgramPaletteColour;	// issue command
}

void ClearScreen()
{
	int i;
	for (i = 0; i < 480; i++)
		WriteHLine(0, 799, i, BLACK);
}

void Rectangle(int x1, int x2, int y1, int y2, int Colour)
{
	int i;
	for (i = y1; i < y2 + 1; i++)
		WriteHLine(x1, x2, i, Colour);
}

void Circle(int x, int y, int radius, int Colour)
{
	WAIT_FOR_GRAPHICS;			// is graphics ready for new command

	GraphicsX1Reg = x;			// write coords to x1, y1
	GraphicsX2Reg = radius;
	GraphicsY1Reg = y;

	GraphicsColourReg = Colour;		// set pixel colour with a palette number
	GraphicsCommandReg = DrawCircle;		// give graphics a "draw Horizontal Line" command
}

// Draw Home Functions
void drawHome() {
	ClearScreen();
	Rectangle(2, 397, 2, 237, MIDNIGHT_BLUE);
	Rectangle(402, 797, 2, 237, MAROON);
	Rectangle(2, 397, 242, 477, DARK_SEA_GREEN);
	Rectangle(402, 797, 242, 477, DARK_MAGENTA);

	char* curSession = "CURRENT SESSION";
	char* prevSession = "PREVIOUS SESSIONS";
	char* achievementString = "ACHIEVEMENTS";
	char* callString = "CALL";

	int i;

	for (i = 0; i < strlen(curSession); i++) {
		OutGraphicsCharFont2a( 80 + i * 15, 118, WHITE, BLACK, curSession[i], 0);
	}
	for (i = 0; i < strlen(prevSession); i++) {
		OutGraphicsCharFont2a( 470 + i * 15, 118, WHITE, BLACK, prevSession[i], 0);
	}
	for (i = 0; i < strlen(achievementString); i++) {
		OutGraphicsCharFont2a( 510 + i * 15, 358, WHITE, BLACK, achievementString[i], 0);
	}
	for (i = 0; i < strlen(callString); i++) {
		OutGraphicsCharFont2a( 170 + i * 15, 358, WHITE, BLACK, callString[i], 0);
	}


}

// Draw Current Session Functions
void drawLog() {
	int i;

	char time_string[DATASIZE];
	sprintf(time_string, "Time: %s", current_time);
	for (i = 0; time_string[i] != '\0'; i++) {
		OutGraphicsCharFont2a( 10 + i * 15, 10, BLACK, WHITE, time_string[i], 0);
	}

	char position_string[4 * DATASIZE];
	sprintf(position_string, "Latitude: %s, Longitude: %s", latitude, longitude);
	for (i = 0; position_string[i] != '\0'; i++) {
		OutGraphicsCharFont2a( 10 + i * 15, 30, BLACK, WHITE, position_string[i], 0);
	}

	char altitude_string[2 * DATASIZE];
	sprintf(altitude_string, "Altitude: %s", altitude);
	for (i = 0; altitude_string[i] != '\0'; i++) {
		OutGraphicsCharFont2a( 10 + i * 15, 50, BLACK, WHITE, altitude_string[i], 0);
	}
}

void eraseLogGUI() {
	Rectangle(2, 797, 2, 80, WHITE);
}

void drawStartButton() {
	// Start
	Rectangle(402, 797, 429, 477, FOREST_GREEN);

	char* startString = "START";
	int i;
	for (i = 0; i < strlen(startString); i++) {
		OutGraphicsCharFont2a( 570 + i * 15, 450, WHITE, BLACK, startString[i], 0);
	}

}

void drawStopButton() {
	// Stop
	Rectangle(402, 797, 429, 477, MAROON);

	char *stopString = "STOP";
	int i;
	for (i = 0; i < strlen(stopString); i++) {
		OutGraphicsCharFont2a( 570 + i * 15, 450, WHITE, BLACK, stopString[i], 0);
	}

}

void drawStartSession() {
	int session_started = 1;
	Rectangle(0, 799, 0, 479, BLACK);
	Rectangle(2, 797, 2, 80, WHITE);

	// Map placeholder
	Rectangle(2, 797, 82, 427, YELLOW);

	// Home
	Rectangle(2, 400, 429, 477, MIDNIGHT_BLUE);

	char* homeString = "HOME";
	int i;
	for (i = 0; i < strlen(homeString); i++) {
		OutGraphicsCharFont2a( 170 + i * 15, 450, WHITE, BLACK, homeString[i], 0);
	}

	drawStartButton();
}

// Draw Call Screen Functions
void drawKeypad() {
	ClearScreen();
	// Draw number area
	Rectangle(2, 797, 2, 80, WHITE);
	// Keypad
	// First Row
	Rectangle(2, 261, 85, 173, DARK_SEA_GREEN);
	Rectangle(265, 526, 85, 173, DARK_SEA_GREEN);
	Rectangle(530, 791, 85, 173, DARK_SEA_GREEN);
	// Second Row
	Rectangle(2, 261, 177, 259, DARK_SEA_GREEN);
	Rectangle(265, 526, 177, 259, DARK_SEA_GREEN);
	Rectangle(530, 791, 177, 259, DARK_SEA_GREEN);
	// Third Row
	Rectangle(2, 261, 263,  345, DARK_SEA_GREEN);
	Rectangle(265, 526, 263,  345, DARK_SEA_GREEN);
	Rectangle(530, 791, 263,  345, DARK_SEA_GREEN);
	// Fourth Row
	Rectangle(2, 261, 349, 425, DARK_SEA_GREEN);
	Rectangle(265, 526, 349, 425, DARK_SEA_GREEN);
	Rectangle(530, 791, 349, 425, DARK_SEA_GREEN);
	// Call Button
	Rectangle(403, 797, 429, 477, FOREST_GREEN);
	// Home Button
	Rectangle(2, 399, 429, 477, MIDNIGHT_BLUE);

	int i;
	char* dialNumber = "123456789";
	char* zero = "0";
	char* one = "1";
	char* two = "2";
	char* three = "3";
	char* four = "4";
	char* five = "5";
	char* six = "6";
	char* seven = "7";
	char* eight = "8";
	char* nine = "9";
	char* clear = "C";
	char* homeString = "HOME";
	char* callString = "CALL";

	OutGraphicsCharFont2a( 400, 380, WHITE, BLACK, zero[0], 0);
	OutGraphicsCharFont2a( 646, 380, WHITE, BLACK, clear[0], 0);

	OutGraphicsCharFont2a( 133, 294, WHITE, BLACK, one[0], 0);
	OutGraphicsCharFont2a( 400, 294, WHITE, BLACK, two[0], 0);
	OutGraphicsCharFont2a( 646, 294, WHITE, BLACK, three[0], 0);

	OutGraphicsCharFont2a( 133, 208, WHITE, BLACK, four[0], 0);
	OutGraphicsCharFont2a( 400, 208, WHITE, BLACK, five[0], 0);
	OutGraphicsCharFont2a( 646, 208, WHITE, BLACK, six[0], 0);

	OutGraphicsCharFont2a( 133, 116, WHITE, BLACK, seven[0], 0);
	OutGraphicsCharFont2a( 400, 116, WHITE, BLACK, eight[0], 0);
	OutGraphicsCharFont2a( 646, 116, WHITE, BLACK, nine[0], 0);

	for (i = 0; i < strlen(homeString); i++) {
		OutGraphicsCharFont2a( 170 + i * 15, 450, WHITE, BLACK, homeString[i], 0);
	}
	for (i = 0; i < strlen(callString); i++) {
		OutGraphicsCharFont2a( 570 + i * 15, 450, WHITE, BLACK, callString[i], 0);
	}

	for (i = 0; i < strlen(dialNumber); i++) {
		OutGraphicsCharFont2a( 10 + i * 15, 40, BLACK, BLACK, dialNumber[i], 0);
	}
}

// Draw Achievement Screen Functions
void drawAchievementsScreen() {
	ClearScreen();
	// White background
	Rectangle(2, 797, 2, 427, WHITE);
	// Home
	Rectangle(202, 599, 429, 477, MIDNIGHT_BLUE);

	char* homeString = "HOME";
	int i;
	for (i = 0; i < strlen(homeString); i++) {
		OutGraphicsCharFont2a( 370 + i * 15, 450, WHITE, BLACK, homeString[i], 0);
	}

}



