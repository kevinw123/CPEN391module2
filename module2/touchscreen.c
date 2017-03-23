#include <stdio.h>
#include "touchscreen.h"

/* Define Address spaces for Touchscreen hardware */
#define TouchScreen_Control (*(volatile unsigned char *)(0x84000230))
#define TouchScreen_Status (*(volatile unsigned char *)(0x84000230))
#define TouchScreen_TxData (*(volatile unsigned char *)(0x84000232))	// input
#define TouchScreen_RxData (*(volatile unsigned char *)(0x84000232))	// output
#define TouchScreen_Baud (*(volatile unsigned char *)(0x84000234))

#define TouchScreen_RxTest (*(volatile unsigned char *)(0x84000233))

/* AR1100 Command Definitions */
#define CMD_TOUCH_ENABLE 0x12
#define CMD_TOUCH_DISABLE 0x13
#define CMD_CALIBRATE 0x14
#define CMD_REG_READ 0x20
#define CMD_REG_WRITE 0x21
#define CMD_EE_READ 0x28
#define CMD_EE_WRITE 0x29
#define CMD_EE_READ_PARAMS 0x2B
#define CMD_EE_WRITE_PARAMS 0x23

/* AR1100 Full Command Packets */
#define CMDP_TOUCH_ENABLE 0x550112
#define CMDP_TOUCH_DISABLE 0x550113
#define CMDP_CALIBRATE 0x55021402 // Last byte corresponds like so:
																		// 0x01 - 4 point Full interpolation
																		// 0x02 - 9 point
																		// 0x03 - 25-point
																		// 0x04 - 4 point (AR1000 style)

/* AR1100 Status Definitions */
#define STATUS_OK 0x00
#define STATUS_UNRECOGNIZED 0x01
#define STATUS_TIMEOUT 0x04
#define STATUS_EEPARAMS_ERR 0x05
#define STATUS_CAL_CANCEL 0xFC
#define STATUS_PRESS_DOWN 0x81
#define STATUS_PRESS_UP 0x80

#define ASPECT_RATIO_SCALE_FACTOR_Y (double) .1953125
#define ASPECT_RATIO_SCALE_FACTOR_X (double) .1171875
#define X_OFFSET_L (int) 420 // 276
#define X_OFFSET_R (int) 4022



/*****************************************************************************
** Initialise touch screen controller
*****************************************************************************/
void Init_Touch(void)
{
 // Program 6850 and baud rate generator to communicate with touchscreen
 // send touchscreen controller an "enable touch" command

	TouchScreen_Control = 0x15;				// TouchScreen 0 00 101 00, PDF only mentions specifications for bits 2-4. Assume 0 for the rest for now.
	TouchScreen_Baud = 0x05;				// TouchScreen requires a baud of 9600.
	Write_Data(CMDP_TOUCH_ENABLE);
}
/*****************************************************************************
** Write Data to touch screen controller
*****************************************************************************/
int Write_Data(int c)
{
	// Poll Tx bit in 6850 status register. Wait for it to become '1' (Transmit data register empty)
  while ((TouchScreen_Status & 2) == 0){
  }
  // Write 'c' to the 6850 TxData register to output the character
  TouchScreen_TxData = c;

	// Poll Rx bit in 6850 status register. Wait for it to become '1' (Data register containing unread char)
	while (TouchScreen_Status & 1 == 0){
	}

	int responsePacket = TouchScreen_RxData;
	int responseStatus = (responsePacket >> (8*2)) & 0xff; // Get the 3rd byte of the response - this is the status code.
	if (responseStatus == 0x00) {
		printf("Response status: OK\n");
		return 1;
	}
	else {
		printf("Response status: %x\n", responseStatus);
		return 0;
	}
	return 0;
}
/*****************************************************************************
** test if screen touched
*****************************************************************************/
int ScreenTouched( void )
{
 // return TRUE if any data received from 6850 connected to touchscreen
 // or FALSE otherwise

// Poll Rx bit in 6850 status register. Wait for it to become '1' (Data register containing unread char)
	if (TouchScreen_Status & 1 == 0){
		return 0;
	}
	return 1;
}
/*****************************************************************************
** wait for screen to be touched
*****************************************************************************/
void WaitForTouch()
{
while(!ScreenTouched())
 ;
}
int getNextByteTouchScreen(void) {
	// Poll Rx bit in Touch Screen status register. Wait for it to become '1'.
	while((TouchScreen_Status & 1) == 0) {
		// Wait for it to become '1'
	}

	// Read received character from 6850 RxData register.
	return TouchScreen_RxData;
}
/*****************************************************************************
* This function waits for a touch screen press event and returns X,Y coord
*****************************************************************************/
Point GetPress(void)
{
 Point p1;
 // wait for a pen down command then return the X,Y coord of the point
 // calibrated correctly so that it maps to a pixel on screen
 // On a pen-down event, the first byte is hex 80.
 //
 int responseHeader;
 do {
	 WaitForTouch();
	 responseHeader = getNextByteTouchScreen();
	 //printf("Response Header = 0x%x\n", responseHeader);
 } while (responseHeader != STATUS_PRESS_DOWN);

 int responsePacket [3];
 int i;
 for (i = 0; i < 4; i++) {
	 responsePacket[i] = getNextByteTouchScreen();
	 //printf("0x%x\n", responsePacket[i]);
 }
 int x_coords_part_1 = responsePacket[0];
 int x_coords_part_2 = responsePacket[1];
 int y_coords_part_1 = responsePacket[2];
 int y_coords_part_2 = responsePacket[3];

 int x_coord = (x_coords_part_1) | (x_coords_part_2 << 7);
 int y_coord = (y_coords_part_1) | (y_coords_part_2 << 7);
 p1.x = compensateX(x_coord) * ASPECT_RATIO_SCALE_FACTOR_X;
 p1.y = y_coord * ASPECT_RATIO_SCALE_FACTOR_Y;
 return p1;
}
/*****************************************************************************
* This function waits for a touch screen release event and returns X,Y coord
*****************************************************************************/
Point GetRelease(void)
{
 Point p1;

 int responseHeader;
  do {
 	 WaitForTouch();
 	 responseHeader = getNextByteTouchScreen();
 	 //printf("Response Header = 0x%x\n", responseHeader);
  } while (responseHeader != STATUS_PRESS_UP || responseHeader == STATUS_PRESS_DOWN);

  int responsePacket [3];
  int i;
  for (i = 0; i < 4; i++) {
 	 responsePacket[i] = getNextByteTouchScreen();
 	 //printf("0x%x\n", responsePacket[i]);
  }
  int x_coords_part_1 = responsePacket[0];
  int x_coords_part_2 = responsePacket[1];
  int y_coords_part_1 = responsePacket[2];
  int y_coords_part_2 = responsePacket[3];

  int x_coord = (x_coords_part_1) | (x_coords_part_2 << 7);
  int y_coord = (y_coords_part_1) | (y_coords_part_2 << 7);
  p1.x = compensateX(x_coord) * ASPECT_RATIO_SCALE_FACTOR_X;
  p1.y = y_coord * ASPECT_RATIO_SCALE_FACTOR_Y;
  return p1;
}

int compensateX (int x)
{
	// 276 4022
	int x_divisor = X_OFFSET_R - X_OFFSET_L;
	int diff = x - X_OFFSET_L;
	if ( diff < 0 ){
		return 0;
	}
	else
	{
		return (int) (diff) * (4096) / x_divisor;
	}
}

Point Get_Touch_Point(void)
{
	while(1) {
		Point p1 = GetPress();
		Point p2 = GetRelease();
		return p1;
	}
}

//int main()
//{
//	// Init touch screen
//	Init_Touch();
//
//	/*
//	 * Test GetPress() - Press Down */
//	while(1) {
//		Point p1 = GetPress();
//		int x1 = p1.x;
//		int y1 = p1.y;
//		printf("Press Down: Scaled X cord is: %i, Scaled Y cord is: %i\n", x1, y1);
//		printf("\n");
//		Point p2 = GetRelease();
//		int x2 = p2.x;
//		int y2 = p2.y;
//		printf("Press Down: Scaled X cord is: %i, Scaled Y cord is: %i\n", x2, y2);
//		printf("\n\n");
//	}
//}
