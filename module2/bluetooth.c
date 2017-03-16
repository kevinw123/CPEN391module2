#include "bluetooth.h"
#include <stdio.h>
#include <stdlib.h>

void initBluetooth() {
	BlueTooth_Baud = 0x01;
	BlueTooth_Control = 0x15;
}

char getcharBluetooth() {
	int rx;
	while ((BlueTooth_Status & 0x01) != 0x01){}
	rx = BlueTooth_RxData;
	return rx;
}


void enterCommandMode() {
	char *initCommand = "$$$";
	usleep(1000000);
	sendStringBluetooth(initCommand);
	printf("Entering Command Mode\n");
	usleep(1000000);
}

void changeName() {
	char *name = "SN,GROUP25TEST\r\n";
	printf("Changing name \n");
	sendStringBluetooth(name);
}

void factoryReset() {
	char *fact_reset = "SF,1\r\n";
	printf("Factory Reseting \n");
	sendStringBluetooth(fact_reset);
}

void setBluetoothPassword() {
	char *password = "SP,0123\r\n";
	printf("Setting Password \n");
	sendStringBluetooth(password);

}

void sendStringBluetooth(char *string) {
	printf("Sending %s\n", string);
	char index;
	while ((index = *string) != 0) {
		while ((BlueTooth_Status & 0x02) != 0x02){}
		BlueTooth_TxData = index & (char) 0x7F;
		string++;
	}
	printf("Finished loop\n");
}
