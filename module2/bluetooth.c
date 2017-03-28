#include "bluetooth.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Setting up the baud rate and control for bluetooth
 */
void initBluetooth() {
	BlueTooth_Baud = 0x01;
	BlueTooth_Control = 0x15;
}

/*
 * Enter command mode by sending $$$ to bluetooth
 * Must wait few seconds before and after sending
 */
void enterCommandMode() {
	char *initCommand = "$$$";
	usleep(1000000);
	sendStringBluetooth(initCommand);
	printf("Command Mode\n");
	usleep(1000000);
}

/*
 * Reads the character from belutooth. Wait for status to become 1 then get the data in RxData
 */
char getcharBluetooth() {
	int character;
	while ((BlueTooth_Status & 0x01) != 0x01){}
	character = BlueTooth_RxData;
	return character;
}

/*
 * Write all characters into TxData register
 */
void sendStringBluetooth(char *string) {
	char index;
	while ((index = *string) != 0) {
		while ((BlueTooth_Status & 0x02) != 0x02){}
		BlueTooth_TxData = index & (char) 0x7F;
		string++;
	}
	printf("**********************BLUETOOTH CHAR SENT\n");
}

/*
 * Change name of bluetooth device calling the command SN, name
 * Ensure to enter command mode first
 */
void changeName() {
	char *name = "SN,GROUP25TEST\r\n";
	sendStringBluetooth(name);
	printf("Name changed\n");
}

/*
 * Factory reset bluetooth device to default settings using SF,1
 * Ensure to enter command mode first
 */
void factoryResetDevice() {
	char *fact_reset = "SF,1\r\n";
	sendStringBluetooth(fact_reset);
	printf("Factory resetted\n");
}

/*
 * Change password of bluetooth device calling the command SP,0123
 * Ensure to enter command mode first
 */
void changePassword() {
	char *password = "SP,0123\r\n";
	sendStringBluetooth(password);
	printf("Password Changed\n");
}


