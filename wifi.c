#include <stdio.h>
#include <time.h>
#include "wifi.h"



void writeReturnNewLine(void) {
	int x = putcharWiFi(13);
	int y = putcharWiFi(10);
}

void Init_WiFi(void)
{
 // Program 6850 and baud rate generator to communicate with GPS
	WiFi_Control = 0x15;			//
	WiFi_Baud = 0x01;				// 115k baud

	writeReturnNewLine();
	printf("%c", getcharWiFi());
	usleep(5000);
	writeReturnNewLine();
	printf("%c", getcharWiFi());
	usleep(5000);
	writeReturnNewLine();
	printf("%c", getcharWiFi());
	usleep(5000);
	writeReturnNewLine();
	printf("%c", getcharWiFi());
	usleep(5000);
	writeReturnNewLine();
	printf("%c", getcharWiFi());
	usleep(5000);


	printf("Wi-Fi Initiated.\n");
}

int putcharWiFi(int c) {
	// Poll Tx bit in 6850 status register. Wait for it to become '1'
	while ((WiFi_Status & 2) == 0){
	}
	// Write 'c' to the 6850 TxData register to output the character
	WiFi_TxData = c;
	return c ;
}

int getcharWiFi(void) {
	while ( (WiFi_Status & 1) == 0) {}
	return WiFi_RxData;
}

int checkIfNewData(void) {
	if ( (WiFi_Status & 1) == 1) {
		return 1;
	}
	return 0;
}

void test_wifi(void)
{
	Init_WiFi();
	char cmd1[(sizeof(SETUP_LUA))-1] = SETUP_LUA;
	char cmd2[(sizeof(SEND_SMS))-1] = SEND_SMS;

	int i,j;

	printf("Sending dofile command...\n");
	for (i = 0; i < ((sizeof(SETUP_LUA)-1)); i++) {
		putcharWiFi((int) cmd1[i]);
		printf("%c",getcharWiFi());
	}
	writeReturnNewLine();
	printf("\n");
	usleep(20000);

	printf("Sending check_wifi() command...\n");
	for (j = 0; j < ((sizeof(SEND_SMS)-1)); j++) {
		putcharWiFi((int) cmd2[j]);
		printf("%c",getcharWiFi());
	}
	writeReturnNewLine();
	//while(1) {
	//	printf("%c", getcharWiFi());
	//}
	printf("\n");
	usleep(20000);
}
