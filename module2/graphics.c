#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Colours.h"
#include "graphics.h"
#include "DrawChar.h"
#include <time.h>
#include <string.h>
//#include "json.h"
//#include "previoussessions.h"

char *lockedAchievementString = "LOCKED";

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

/*
 * Function to clear the screen by drawing a black rectangle for the whole screen
 */
void ClearScreen()
{
	int i;
	for (i = 0; i < 480; i++)
		WriteHLine(0, 799, i, BLACK);
}

/*
 * Function that draws rectangle by drawing a line from x1 to x2 froom y1 to y2
 */
void Rectangle(int x1, int x2, int y1, int y2, int Colour)
{
	int i;
	for (i = y1; i < y2; i++)
		WriteHLine(x1, x2-1, i, Colour);
}

/*
 * Function that draws circle at given coordinate x and y with given radious
 */
void Circle(int x, int y, int radius, int Colour)
{
	WAIT_FOR_GRAPHICS;			// is graphics ready for new command

	GraphicsX1Reg = x;			// write coords to x1, y1
	GraphicsX2Reg = radius;
	GraphicsY1Reg = y;

	GraphicsColourReg = Colour;		// set pixel colour with a palette number
	GraphicsCommandReg = DrawCircle;		// give graphics a "draw Horizontal Line" command
}

/*
 * Function to initialize the 256 colour palettes
 */
void initializeColours() {
	int i, j, k;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			for (k = 0; k < 4; k++)
				ProgramPalette(32 * i + 4 * j + k, (0x24 * i << 16) + (0x24 * j << 8) + 0x55 * k);
		}
	}
}

/*
 * Function that displays text on the screen by given x and y values and text color
 */
void drawString(char *string, int x, int y, int fontcolour, int backgroundcolour) {
	int i;
	for (i = 0; i < strlen(string); i++) {
		OutGraphicsCharFont2a( x + i * 15, y, fontcolour, backgroundcolour, string[i], 0);
	}
}

void drawStringSmallFont(char *string, int x, int y, int fontcolour, int backgroundcolour) {
	int i;
	for (i = 0; i < strlen(string); i++) {
		OutGraphicsCharFont1(x + i * 10, y, fontcolour, backgroundcolour, string[i], 0);
	}
}



