// #defined constants representing values we write to the graphics 'command' register to get
// it to do something. You will add more values as you add hardware to the graphics chip
// Note DrawHLine, DrawVLine and DrawLine at the moment do nothing - you will modify these

#define DrawHLine		1
#define DrawVLine		2
#define DrawLine		3
#define DrawCircle  4
#define PutAPixel		0xA
#define GetAPixel		0xB
#define ProgramPaletteColour   	0x10

/*******************************************************************************************
** This macro pauses until the graphics chip status register indicates that it is idle
*******************************************************************************************/

#define WAIT_FOR_GRAPHICS		while((GraphicsStatusReg & 0x0001) != 0x0001);

//Predefined Colour Values
//Use the symbolic constants below as the values to write to the Colour Register
//When you ask the graphics chip to draw something. These values are also returned
//By the read pixel command

// the header file "Colours.h" contains symbolic names for all 256 colours e.g. RED
// while the source file ColourPaletteData.c contains the 24 bit RGB data
// that is pre-programmed into each of the 256 palettes


#define GraphicsCommandReg   	(*(volatile unsigned short int *)(0x84000000))
#define GraphicsStatusReg   	(*(volatile unsigned short int *)(0x84000000))
#define GraphicsX1Reg   		(*(volatile unsigned short int *)(0x84000002))
#define GraphicsY1Reg   		(*(volatile unsigned short int *)(0x84000004))
#define GraphicsX2Reg   		(*(volatile unsigned short int *)(0x84000006))
#define GraphicsY2Reg			(*(volatile unsigned short int *)(0x84000008))
#define GraphicsColourReg		(*(volatile unsigned short int *)(0x8400000E))
#define GraphicsBackGroundColourReg   		(*(volatile unsigned short int *)(0x84000010))


// Function prototypes
void WriteAPixel (int x, int y, int Colour);
void WriteHLine (int x1, int x2, int y, int Colour);
void WriteVLine (int x, int y1, int y2, int Colour);
void WriteLine (int x1, int x2, int y1, int y2, int Colour);
void ClearScreen();
void Rectangle(int x1, int x2, int y1, int y2, int Colour);
void Circle(int x, int y, int radius, int Colour);
void drawString(char *string, int x, int y, int fontcolour, int backgroundcolour);
void drawHome();
void drawKeypad();
void drawLog();
void eraseLogGUI();
void drawStartButton();
void drawStopButton();
void drawStartSession();
void drawAchievementsScreen();
void drawPreviouSession();
int ReadAPixel (int x, int y);
void ProgramPalette(int PaletteNumber, int RGB);
char* dialNumber;
int dialIndex;
void printDialNumber(char number, int dialIndex);
void clearNumberScreen();
void drawMap();
int validPointOnScreen(int x, int y);
void VRectangle(int x1, int x2, int y1, int y2, int Colour);
