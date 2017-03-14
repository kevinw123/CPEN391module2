#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BlueTooth_Control (*(volatile unsigned char *)(0x84000220))
#define BlueTooth_Status (*(volatile unsigned char *)(0x84000220))
#define BlueTooth_TxData (*(volatile unsigned char *)(0x84000222))
#define BlueTooth_RxData (*(volatile unsigned char *)(0x84000222))
#define BlueTooth_Baud (*(volatile unsigned char *)(0x84000224))

void initBluetooth(void) {
	BlueTooth_Baud = 0x01;
	BlueTooth_Control = 0x15;
}

char getcharBluetooth(void) {
	int rx;
	while ((BlueTooth_Status & 0x01) != 0x01){}

	rx = BlueTooth_RxData;
	//printf("Receiving : %c\n", rx);
	return rx;
}

/*
 * Enter command mode by sending $$$ followed by waiting for a few seconds
 * After sending to bluetooth dongle, wait for a few more seconds
 */
void enterCommandMode(void) {
	char *commandInit = "$$$";
	usleep(1000000);
	sendStringBluetooth(commandInit);
	printf("Enter Command Mode\n");
	usleep(1000000);
}

/*
 * Change the name of the bluetooth dongle
 * by sending SN,"newname" command
 */
void changeName(void) {
	char *name = "SN,GROUP25TEST\r\n";
	printf("setting device name \n");
	sendStringBluetooth(name);
}

/*
 * Factory reset the bluetooth dongle by
 * sending SF,1 command
 */
void factoryReset(void) {
	char *fact_reset = "SF,1\r\n";
	printf("factory fact_resetting \n");
	sendStringBluetooth(fact_reset);
}

/*
 * Setting password of bluetooth
 * by sending "SP,"newpassword"" command
 */
void setBluetoothPassword(void) {
	char *password = "SP,0123\r\n";
	printf("setting device password \n");
	sendStringBluetooth(password);
}

/*
 * Sending string to Bluetooth dongle
 */
void sendStringBluetooth(char *s) {
	char index;
	while ((index = *s) != 0) {
		while ((BlueTooth_Status & 0x02) != 0x02)
		;
		BlueTooth_TxData = index & (char) 0x7F;
		s++;
	}
}

char getBluetoothCommand(void) {
	char result;
	while(1){
		char a = getcharBluetooth();
		if(a == '$'){
			break;
		}
		else if (atoi(a) > 1 && atoi(a) < 23){
			result = a;
		} 
		else {
			continue;
		}
		printf("Receiving : %c\n", a);
	}
	return result;
}

// int main()
// {
// 	initBluetooth();
// 	//enterCommandMode();
// 	//changeName();
// 	//setBluetoothPassword();
// 	while(1){
// 		char a = getcharBluetooth();
// 		if(a == '$'){
// 			break;
// 		}
// 		printf("Receiving : %c\n", a);
// 	}
// 	/*char *testString = "hello$";
// 	sendStringBluetooth(testString);*/
// 	printf("done");
// 	return 0;
// }
