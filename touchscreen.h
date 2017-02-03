/*
 * touchscreen.h
 *
 *  Created on: 2017-02-01
 *      Author: ahboo
 */

#ifndef TOUCHSCREEN_H_
#define TOUCHSCREEN_H_


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

/* a data type to hold a point/coord */
typedef struct { int x, y; } Point ;

int compensateX (int x);
Point GetRelease(void);
Point GetPress(void);
int ScreenTouched( void );
void WaitForTouch();
int Write_Data(int c);
void Init_Touch(void);
Point Get_Touch_Point(void);

#endif /* TOUCHSCREEN_H_ */
