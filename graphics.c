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

void WriteVLine (int x, int y1, int y2, int Colour)
{
	WAIT_FOR_GRAPHICS;			// is graphics ready for new command

	GraphicsX1Reg = x;			// write coords to x1, y1
	GraphicsY1Reg = y1;
	GraphicsY2Reg = y2;

	GraphicsColourReg = Colour;		// set pixel colour with a palette number
	GraphicsCommandReg = DrawVLine;		// give graphics a "draw Horizontal Line" command
}

void WriteLine (int x1, int x2, int y1, int y2, int Colour)
{
	WAIT_FOR_GRAPHICS;			// is graphics ready for new command

	GraphicsX1Reg = x1;			// write coords to x1, y1
	GraphicsX2Reg = x2;
	GraphicsY1Reg = y1;
	GraphicsY2Reg = y2;

	GraphicsColourReg = Colour;		// set pixel colour with a palette number
	GraphicsCommandReg = DrawLine;		// give graphics a "draw Horizontal Line" command
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

void drawString(char *string, int x, int y, int fontcolour, int backgroundcolour) {
	int i;
	for (i = 0; i < strlen(string); i++) {
		OutGraphicsCharFont2a( x + i * 15, y, fontcolour, backgroundcolour, string[i], 0);
	}
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

	drawString(curSession, 80, 118, WHITE, BLACK);
	drawString(prevSession, 470, 118, WHITE, BLACK);
	drawString(achievementString, 510, 358, WHITE, BLACK);
	drawString(callString, 170, 358, WHITE, BLACK);
}

// Draw Current Session Functions
void drawLog() {

	char time_string[DATASIZE];
	sprintf(time_string, "Time: %s, Time Elapsed: %s", current_time, time_elapsed);
	drawString(time_string, 10, 10, BLACK, WHITE);

	char position_string[4 * DATASIZE];
	sprintf(position_string, "Lat: %s, Long: %s, Alt: %s", latitude, longitude, altitude);
	drawString(position_string, 10, 30, BLACK, WHITE);

	char distance_speed_string[DATASIZE];
	sprintf(distance_speed_string, "Distance: %s, Speed: %s", distance, speed);
	drawString(distance_speed_string, 10, 50, BLACK, WHITE);
}

void eraseLogGUI() {
	Rectangle(2, 797, 2, 80, WHITE);
}

void drawStartButton() {

	Rectangle(402, 797, 429, 477, FOREST_GREEN);

	char* startString = "START";
	drawString(startString, 570, 450, WHITE, BLACK);
}

void drawStopButton() {

	Rectangle(402, 797, 429, 477, MAROON);

	char *stopString = "STOP";
	drawString(stopString, 570, 450, WHITE, BLACK);
}

void drawMap() {
	Rectangle(2, 797, 82, 427, LIGHT_GREEN);
	// Main Mall
	Rectangle(2, 797, 88, 114, SILVER);

	// Agronomy Road
	Rectangle(8, 34, 82, 427, SILVER);

	// Engineering Road
	Rectangle(2, 500, 241, 267, SILVER);
	Rectangle(474, 500 , 267, 395, SILVER);

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
	char *engineeringString = "Engineering Road";

	drawString(macleodString, 520, 177, BLACK, WHITE);
	drawString(cemeString, 690, 320, BLACK, WHITE);
	drawString(edcString, 560, 320, BLACK, WHITE);
	drawString(icicsString, 150, 177, BLACK, WHITE);
	drawString(dmpString, 80, 328, BLACK, WHITE);
	drawString(engCoopString, 205, 328, BLACK, WHITE);
	drawString(ampelString, 350, 328, BLACK, WHITE);
	drawString(mainMallString, 520, 93, BLACK, WHITE);
	drawString(eastMallString, 520, 399, BLACK, WHITE);
	drawString(engineeringString, 80, 245, BLACK, WHITE);

	for (i = 0; i < strlen(agronomyString); i++) {
		OutGraphicsCharFont2a( 14, 100 + i * 15, BLACK, WHITE, agronomyString[i], 0);
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
	drawString(homeString, 170, 450, WHITE, BLACK);

	drawStartButton();
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
	drawString(homeString, 170, 450, WHITE, BLACK);
	drawString(nextString, 570, 450, WHITE, BLACK);

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

	drawString(homeString, 170, 450, WHITE, BLACK);
	drawString(callString, 570, 450, WHITE, BLACK);
}

// Clear the keypad number screen
void clearNumberScreen() {
	Rectangle(2, 797, 2, 80, WHITE);
}

// Prints the number pressed on keypad
void printDialNumber(char number, int dialIndex) {
	OutGraphicsCharFont2a(dialIndex, 40, BLACK, BLACK, number, 0);
}

int distance1_achieved = 1;
int distance2_achieved = 1;
int session1_achieved = 1;
int session2_achieved = 1;
int speed1_achieved = 1;
int speed2_achieved = 1;
int achievementsRadius = 80;
char *lockedAchievementString = "LOCKED";

void drawLockedAchievement(int x, int y) {
	Circle(x, y , achievementsRadius, BLACK);
	drawString(lockedAchievementString, x - 40, y - 5, WHITE, BLACK);
}

void drawAchievementDistance1() {
	int x = 120;
	int y = 100;
	if (distance1_achieved) {
		Circle(x, y, achievementsRadius, DARK_MAGENTA);
		char *achievementString1 = "100 M IN";
		drawString(achievementString1, x - 55, y - 15, WHITE, BLACK);
		char *achievementString2 = "A SESSION";
		drawString(achievementString2, x - 60, y + 5, WHITE, BLACK);

	} else {
		drawLockedAchievement(x, y);
	}
}

void drawAchievementDistance2() {
	int x = 120;
	int y = 300;
	if (distance2_achieved) {
		Circle(x, y, achievementsRadius, DARK_MAGENTA);
		char *achievementString1 = "500 M IN";
		drawString(achievementString1, x - 55, y - 15, WHITE, BLACK);
		char *achievementString2 = "A SESSION";
		drawString(achievementString2, x - 60, y + 5, WHITE, BLACK);
	} else {
		drawLockedAchievement(x, y);
	}
}

void drawAchievementSession1() {
	int x = 399;
	int y = 100;
	if (session1_achieved) {
		Circle(x, y, achievementsRadius, TEAL);
		char *achievementString1 = "3 SESSIONS";
		drawString(achievementString1, x - 70, y - 15, WHITE, BLACK);
		char *achievementString2 = "COMPLETED";
		drawString(achievementString2, x - 60, y + 5, WHITE, BLACK);
	} else {
		drawLockedAchievement(x, y);
	}
}

void drawAchievementSession2() {
	int x = 399;
	int y = 300;
	if (session2_achieved) {
		Circle(x, y, achievementsRadius, TEAL);
		char *achievementString1 = "5 SESSIONS";
		drawString(achievementString1, x - 70, y - 15, WHITE, BLACK);
		char *achievementString2 = "COMPLETED";
		drawString(achievementString2, x - 60, y + 5, WHITE, BLACK);
	} else {
		drawLockedAchievement(x, y);
	}
}

void drawAchievementSpeed1() {
	int x = 678;
	int y = 100;
	if (speed1_achieved) {
		Circle(x, y, achievementsRadius, MEDIUM_VIOLET_RED);
		char *achievementString1 = "REACHED";
		drawString(achievementString1, x - 45, y - 15, WHITE, BLACK);
		char *achievementString2 = "3 M/S";
		drawString(achievementString2, x - 30, y + 5, WHITE, BLACK);
	} else {
		drawLockedAchievement(x, y);
	}
}

void drawAchievementSpeed2() {
	int x = 678;
	int y = 300;
	if (speed2_achieved) {
		Circle(x, y, achievementsRadius, MEDIUM_VIOLET_RED);
		char *achievementString1 = "REACHED";
		drawString(achievementString1, x - 45, y - 15, WHITE, BLACK);
		char *achievementString2 = "5 M/S";
		drawString(achievementString2, x - 30, y + 5, WHITE, BLACK);
	} else {
		drawLockedAchievement(x, y);
	}

}

// Draw Achievement Screen Functions
void drawAchievementsScreen() {
	ClearScreen();
	// White background
	Rectangle(2, 797, 2, 427, WHITE);
	// Home
	Rectangle(202, 599, 429, 477, MIDNIGHT_BLUE);
	drawAchievementDistance1();
	drawAchievementDistance2();
	drawAchievementSession1();
	drawAchievementSession2();
	drawAchievementSpeed1();
	drawAchievementSpeed2();

	char* homeString = "HOME";
	drawString(homeString, 370, 450, WHITE, BLACK);
}



