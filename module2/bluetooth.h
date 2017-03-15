/*
 * bluetooth.h
 *
 *  Created on: Mar 14, 2017
 *      Author: Kevin Wong
 */

#define BlueTooth_Control (*(volatile unsigned char *)(0x84000220))
#define BlueTooth_Status (*(volatile unsigned char *)(0x84000220))
#define BlueTooth_TxData (*(volatile unsigned char *)(0x84000222))
#define BlueTooth_RxData (*(volatile unsigned char *)(0x84000222))
#define BlueTooth_Baud (*(volatile unsigned char *)(0x84000224))

void initBluetooth();
char getcharBluetooth();
void enterCommandMode();
void changeName();
void factoryReset();
void setBluetoothPassword();
void sendStringBluetooth(char *string);
