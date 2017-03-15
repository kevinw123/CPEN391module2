#include<stdio.h>
#include<stdlib.h>
/**
 * M68xxIODecoder.vhd: register addresses
 * ACIA_6850.vhd: information inside the register bits
 * ACIA_BaudRate_Generator.bdf: 3-bit values for setting the baud rate
 * OnChipM68xxIO.bdf: connections between M68xxIODecoder and each ACIA_6850 + baud generator
 */

#define RS232_Control (*(volatile unsigned char *)(0x84000200))
#define RS232_Status (*(volatile unsigned char *)(0x84000200))
#define RS232_TxData (*(volatile unsigned char *)(0x84000202))
#define RS232_RxData (*(volatile unsigned char *)(0x84000202))
#define RS232_Baud (*(volatile unsigned char *)(0x84000204))

/*
#define GPS_Control (*(volatile unsigned char *)(0x84000210))
#define GPS_Status (*(volatile unsigned char *)(0x84000210))
#define GPS_TxData (*(volatile unsigned char *)(0x84000212))
#define GPS_RxData (*(volatile unsigned char *)(0x84000212))
#define GPS_Baud (*(volatile unsigned char *)(0x84000214))
*/
#define BlueTooth_Control (*(volatile unsigned char *)(0x84000220))
#define BlueTooth_Status (*(volatile unsigned char *)(0x84000220))
#define BlueTooth_TxData (*(volatile unsigned char *)(0x84000222))
#define BlueTooth_RxData (*(volatile unsigned char *)(0x84000222))
#define BlueTooth_Baud (*(volatile unsigned char *)(0x84000224))
/*
#define TouchScreen_Control (*(volatile unsigned char *)(0x84000230))
#define TouchScreen_Status (*(volatile unsigned char *)(0x84000230))
#define TouchScreen_TxData (*(volatile unsigned char *)(0x84000232))
#define TouchScreen_RxData (*(volatile unsigned char *)(0x84000232))
#define TouchScreen_Baud (*(volatile unsigned char *)(0x84000234))

#define WiFi_Control (*(volatile unsigned char *)(0x84000240))
#define WiFi_Status (*(volatile unsigned char *)(0x84000240))
#define WiFi_TxData (*(volatile unsigned char *)(0x84000242))
#define WiFi_RxData (*(volatile unsigned char *)(0x84000242))
#define WiFi_Baud (*(volatile unsigned char *)(0x84000244))
*/

void Init_RS232(void){
	// Set up 6850 Control Register to utilize a divide by 16 clock,
	// Set RTS low, use 8 bits of data, no parity, 1 stop bit,
	// Transmitter interrupt disabled
	// Program baud rate generator to use 115k baud
	RS232_Control = 0x15;  // 0 00 101 01
	RS232_Baud = 0x01;
}

int putcharRS232(int c){
	// Poll Tx bit in 6850 status register. Wait for it to become '1'
	while ((RS232_Status & 2) == 0){
	}
	// Write 'c' to the 6850 TxData register to output the character
	RS232_TxData = c;
	return c ;
}

int getcharRS232(void){
	// Poll Rx bit in 6850 status register. Wait for it to become '1'.
	while (RS232_Status & 1 == 0){
		// Wait for it to become '1'
	}

	// Read received character from 6850 RxData register.
	return RS232_RxData;
}

int RS232testForReceivedData(void){
	// Test Rx bit in 6850 serial comms chip status register
	// If Rx bit is set, return TRUE, otherwise return FALSE
	if ((RS232_Status & 1) == 1){
		return 1;
	}

	return 0;
}

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


void enterCommandMode(void) {
	char *commandInit = "$$$";
	usleep(1000000);
	sendStringBluetooth(commandInit);
	printf("Enter Command Mode\n");
	usleep(1000000);
}

void changeName(void) {

	char *name = "SN,GROUP25TEST\r\n";
	printf("setting device name \n");
	sendStringBluetooth(name);
}

void factoryReset(void) {
	char *fact_reset = "SF,1\r\n";
	printf("factory fact_resetting \n");
	sendStringBluetooth(fact_reset);
}

void setBluetoothPassword(void) {

	char *password = "SP,0123\r\n";
	printf("setting device password \n");
	sendStringBluetooth(password);

}

void sendStringBluetooth(char *s) {
	char index;
	while ((index = *s) != 0) {

		while ((BlueTooth_Status & 0x02) != 0x02)
		;

		BlueTooth_TxData = index & (char) 0x7F;
		s++;
	}
	printf("Finished loop");
}

int main5()
{
	initBluetooth();
	//enterCommandMode();
	//changeName();
	//setBluetoothPassword();
	while(1){
		char a = getcharBluetooth();
		if(a == '$'){
			break;
		}
		printf("Receiving : |%c|\n", a);
	}
	/*char *testString = "hello$";
	sendStringBluetooth(testString);*/
	printf("done");
	return 0;
}
