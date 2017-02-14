#include <stdio.h>
#include <time.h>
#include "wifi.h"
#include <string.h>



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

	sendCommand(SETUP_LUA);
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

void sendCommand(char *string)
{
	int i;
	for (i = 0; i < strlen(string); i++)
	{
		putcharWiFi(string[i]);
		//printf("%c", getcharWiFi());
	}
	writeReturnNewLine();
}

char* createInsertCommand(char *start_lat, char *start_long, char *end_lat, char *end_long, char *start_time, char *end_time, char *total_distance, char *speed)
{
	char *command;
	char *literal_start = "insertDB(";
	char *literal_end = ")";
	int cmd_size = strlen(literal_start) + strlen(start_lat) + strlen(start_long) + strlen(end_lat) + strlen(end_long) + strlen(start_time) + strlen(end_time) + strlen(total_distance) + strlen(speed) + strlen(literal_end);
	char cmd[cmd_size + 50];
	strcpy(cmd, literal_start);
	strcat(cmd, "\"");
	strcat(cmd, start_lat);
	strcat(cmd, "\",\"");
	strcat(cmd, start_long);
	strcat(cmd, "\",\"");
	strcat(cmd, end_lat);
	strcat(cmd, "\",\"");
	strcat(cmd, end_long);
	strcat(cmd, "\",\"");
	strcat(cmd, start_time);
	strcat(cmd, "\",\"");
	strcat(cmd, end_time);
	strcat(cmd, "\",\"");
	strcat(cmd, total_distance);
	strcat(cmd, "\",\"");
	strcat(cmd, speed);
	strcat(cmd, "\"");
	strcat(cmd, literal_end);
	strcpy(command, cmd);
	return command;
}

char* createCallCommand(char *numberToCall)
{
	// twilioCall(numberToCall)
	char *command;
	char *literal_start = "twilioCall(";
	char *literal_end = ")";
	int cmd_size = strlen(literal_start) + strlen(numberToCall) + strlen(literal_end);
	char cmd[cmd_size + 50];
	strcpy(cmd, literal_start);
	strcat(cmd, "\"+1");
	strcat(cmd, numberToCall);
	strcat(cmd, "\"");
	strcat(cmd, literal_end);
	strcpy(command, cmd);
	return command;
}


