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
	sprintf(time_string, "Time: %s, Time Elapsed: %s", current_time, time_elapsed);
	for (i = 0; time_string[i] != '\0'; i++) {
		OutGraphicsCharFont2a( 10 + i * 15, 10, BLACK, WHITE, time_string[i], 0);
	}

	char position_string[4 * DATASIZE];
	sprintf(position_string, "Lat: %s, Long: %s, Alt: %s", latitude, longitude, altitude);
	for (i = 0; position_string[i] != '\0'; i++) {
		OutGraphicsCharFont2a( 10 + i * 15, 30, BLACK, WHITE, position_string[i], 0);
	}

	char distance_speed_string[DATASIZE];
	sprintf(distance_speed_string, "Distance: %s, Speed: %s", distance, speed);
	for (i = 0; distance_speed_string[i] != '\0'; i++) {
		OutGraphicsCharFont2a( 10 + i * 15, 50, BLACK, WHITE, distance_speed_string[i], 0);
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

void drawMap(){
	Rectangle(2, 797, 82, 427, LIGHT_GREEN);
	// Main Mall
	Rectangle(2, 797, 88, 114, SILVER);

	// Agronomy Road
	Rectangle(8, 34, 82, 427, SILVER);

	// Engineering Road
	Rectangle(2, 500, 241, 267, SILVER);
	Rectangle(474, 500 ,267, 395, SILVER);

	// East Mall
	Rectangle(2, 797, 395, 421, SILVER);

	// Macleod
	Rectangle(400, 780, 116, 238, PEACH_PUFF);

	// CEME
	Rectangle(660, 780, 250, 390, PEACH_PUFF);
	// EDC
	Rectangle(510, 650, 250, 390, PEACH_PUFF);

	// ICICS
	Rectangle(40, 350, 116, 238, PEACH_PUFF);

	// DMP
	Rectangle(36, 165, 269, 393, PEACH_PUFF);
	// Engineering Co-op Office
	Rectangle(170, 295, 269, 393, PEACH_PUFF);
	// Advanced Materials Process Engineering Labatory
	Rectangle(300, 472, 269, 393, PEACH_PUFF);

	// Draw Text
	int i;
	char* macleodString = "MacLeod";
	char* cemeString = "CEME";
	char* edcString = "EDC";

	char* icicsString = "ICICS";
	char* dmpString = "DMP";
	char* engCoopString = "Co-op";
	char* ampelString = "AMPEL";

	char* mainMallString = "Main Mall";
	char* eastMallString = "East Mall";
	char* agronomyString = "Agronomy Road";


	for (i = 0; i < strlen(macleodString); i++) {
		OutGraphicsCharFont2a( 520 + i * 15, 177, BLACK, BLACK, macleodString[i], 0);
	}

	for (i = 0; i < strlen(cemeString); i++) {
		OutGraphicsCharFont2a( 690 + i * 15, 320, BLACK, BLACK, cemeString[i], 0);
	}

	for (i = 0; i < strlen(edcString); i++) {
		OutGraphicsCharFont2a( 560 + i * 15, 320, BLACK, BLACK, edcString[i], 0);
	}

	for (i = 0; i < strlen(icicsString); i++) {
		OutGraphicsCharFont2a( 150 + i * 15, 177, BLACK, BLACK, icicsString[i], 0);
	}

	for (i = 0; i < strlen(dmpString); i++) {
		OutGraphicsCharFont2a( 80 + i * 15, 328, BLACK, BLACK, dmpString[i], 0);
	}


	for (i = 0; i < strlen(engCoopString); i++) {
		OutGraphicsCharFont2a( 205 + i * 15, 328, BLACK, BLACK, engCoopString[i], 0);
	}

	for (i = 0; i < strlen(ampelString); i++) {
		OutGraphicsCharFont2a( 350 + i * 15, 328, BLACK, BLACK, ampelString[i], 0);
	}

	for (i = 0; i < strlen(mainMallString); i++) {
		OutGraphicsCharFont2a( 520 + i * 15, 93, BLACK, BLACK, mainMallString[i], 0);
	}
	for (i = 0; i < strlen(eastMallString); i++) {
		OutGraphicsCharFont2a( 520 + i * 15, 399, BLACK, BLACK, eastMallString[i], 0);
	}
	for (i = 0; i < strlen(agronomyString); i++) {
		OutGraphicsCharFont2a( 14, 100 + i * 15, BLACK, BLACK, agronomyString[i], 0);
	}
}
void drawStartSession() {
	int session_started = 1;
	Rectangle(0, 799, 0, 479, BLACK);
	Rectangle(2, 797, 2, 80, WHITE);

	drawMap();

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

}

// Clear the keypad number screen
void clearNumberScreen(){
	Rectangle(2, 797, 2, 80, WHITE);
}

// Prints the number pressed on keypad
void printDialNumber(char number, int dialIndex){
	OutGraphicsCharFont2a(dialIndex, 40, BLACK, BLACK, number, 0);
}

// Draw Achievement Screen Functions
void drawAchievementsScreen() {
	ClearScreen();
	// White background
	Rectangle(2, 797, 2, 427, WHITE);
	// Home
	Rectangle(202, 599, 429, 477, MIDNIGHT_BLUE);
	// First row of achievements
	Circle(120, 100 , 80, BLACK);
	Circle(399, 100 , 80, BLACK);
	Circle(678, 100 , 80, BLACK);
	// Second row of achievements
	Circle(120, 300 , 80, BLACK);
	Circle(399, 300 , 80, BLACK);
	Circle(678, 300 , 80, BLACK);

	char* homeString = "HOME";
	int i;
	for (i = 0; i < strlen(homeString); i++) {
		OutGraphicsCharFont2a( 370 + i * 15, 450, WHITE, BLACK, homeString[i], 0);
	}

}

// Draw Previous Session Screen
void drawPreviouSession() {
	ClearScreen();
	// Entries
	Rectangle(2, 797, 2, 102, WHITE);
	Rectangle(2, 797, 106, 206, WHITE);
	Rectangle(2, 797, 210, 310, WHITE);
	Rectangle(2, 797, 314, 414, WHITE);
	// Next Page Button
	Rectangle(403, 797, 429, 477, FOREST_GREEN);
	// Home Button
	Rectangle(2, 399, 429, 477, MIDNIGHT_BLUE);
	char* homeString = "HOME";
	char* nextString = "NEXT";
	int i;
	for (i = 0; i < strlen(homeString); i++) {
		OutGraphicsCharFont2a( 170 + i * 15, 450, WHITE, BLACK, homeString[i], 0);
	}
	for (i = 0; i < strlen(nextString); i++) {
		OutGraphicsCharFont2a( 570 + i * 15, 450, WHITE, BLACK, nextString[i], 0);
	}
}



